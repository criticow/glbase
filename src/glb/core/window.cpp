#include "window.hpp"

std::mutex Window::framebufferMutex;
std::mutex Window::cursorPosMutex;

Window::Window(int width, int height, const char* title, bool centered)
{
  this->width = width;
  this->height = height;
  this->mouse.lastX = this->width * 0.5f;
  this->mouse.lastY = this->height * 0.5f;

  ASSERT(glfwInit(), "Could not initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  #ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  #endif

  this->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  ASSERT(this->handle, "Could not create window");
  LOGGER_DEBUG("Created Window");

  if(centered)
  {
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    int offsetX, offsetY, windowWidth, windowHeight;

    glfwGetMonitorPos(primaryMonitor, &offsetX, &offsetY);
    glfwGetWindowSize(this->handle, &windowWidth, &windowHeight);
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    glfwSetWindowPos(this->handle, offsetX + (mode->width - windowWidth) / 2, offsetY + (mode->height - windowHeight) / 2);
    LOGGER_DEBUG("Centered Window");
  }

  // Window callbacks
  glfwSetFramebufferSizeCallback(this->handle, this->framebufferSizeCallback);
  glfwSetCursorPosCallback(this->handle, cursorPosCallback);
}

void Window::loadOpenGL()
{
  glfwMakeContextCurrent(this->handle);

  ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Could not load OpenGL");

  LOGGER_DEBUG("Loaded OpenGL: {}.{}", GLVersion.major, GLVersion.minor);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_MULTISAMPLE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if(flags & GL_CONTEXT_FLAG_DEBUG_BIT)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(this->glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    LOGGER_DEBUG("Set OpenGL Debugger");
  }

  this->isOpenglLoaded = true;
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose(this->handle);
}

void Window::swapBuffers()
{
  glfwSwapBuffers(this->handle);
}

void Window::pollEvents()
{
  glfwPollEvents();
}

void Window::waitEvents()
{
  glfwWaitEvents();
}

void Window::destroy()
{
  glfwTerminate();
  LOGGER_DEBUG("Destroyed Window");
}

void Window::hideCursor()
{
  glfwSetInputMode(this->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::setTitle(const std::string &title)
{
  glfwSetWindowTitle(this->handle, title.c_str());
}

void Window::setUserPointer()
{
  glfwSetWindowUserPointer(this->handle, this);
}

void Window::updateViewport()
{
  ASSERT(this->isOpenglLoaded, "OpenGL is not loaded");

  this->framebufferMutex.lock();
  if(this->isFramebufferUpdated)
  {
    this->isFramebufferUpdated = false;
    glViewport(0, 0, this->width, this->height);
  }
  this->framebufferMutex.unlock();
}

void Window::close()
{
  glfwSetWindowShouldClose(this->handle, GLFW_TRUE);
}

void Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setIcon(const std::string &folder)
{
  std::filesystem::path path(folder);
  std::vector<std::string> images;

  try
  {
    if(std::filesystem::is_directory(path))
    {
      for(const auto &entry : std::filesystem::directory_iterator(path))
      {
        images.push_back(entry.path().string());
      }
    }
    else
    {
      images.push_back(folder);
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  std::vector<GLFWimage> icons(images.size());
  
  for(size_t i = 0; i < images.size(); i++)
  {
    icons[i].pixels = stbi_load(images[i].c_str(), &icons[i].width, &icons[i].height, nullptr, 4);
  }

  // Set the window icon
  glfwSetWindowIcon(this->handle, images.size(), icons.data());

  for(auto &icon : icons)
  {
    stbi_image_free(icon.pixels);
  }
}

void Window::framebufferSizeCallback(GLFWwindow *handle, int width, int height)
{
  // Do nothing
  if(width == 0 || height == 0)
  {
    return;
  }

  Window *windowPointer = reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle));
  ASSERT(windowPointer, "Could not find window user pointer");

  windowPointer->framebufferMutex.lock();
  windowPointer->isFramebufferUpdated = true;
  windowPointer->width = width;
  windowPointer->height = height;
  windowPointer->framebufferMutex.unlock();
}

void Window::glDebugOutput(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei len, const char *msg, const void *usrParam)
{
  // ignore non-significant error/warning codes
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::ostringstream sstream;

  sstream << "\nDebug message (" << id << "): " << msg << "\n";

  switch (src)
  {
    case GL_DEBUG_SOURCE_API:             sstream << "Source: API\n"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sstream << "Source: Window System\n"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sstream << "Source: Shader Compiler\n"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     sstream << "Source: Third Party\n"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     sstream << "Source: Application\n"; break;
    case GL_DEBUG_SOURCE_OTHER:           sstream << "Source: Other\n"; break;
  }

  switch (type)
  {
    case GL_DEBUG_TYPE_ERROR:               sstream << "Type: Error\n"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: sstream << "Type: Deprecated Behaviour\n"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  sstream << "Type: Undefined Behaviour\n"; break; 
    case GL_DEBUG_TYPE_PORTABILITY:         sstream << "Type: Portability\n"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         sstream << "Type: Performance\n"; break;
    case GL_DEBUG_TYPE_MARKER:              sstream << "Type: Marker\n"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          sstream << "Type: Push Group\n"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           sstream << "Type: Pop Group\n"; break;
    case GL_DEBUG_TYPE_OTHER:               sstream << "Type: Other\n"; break;
  }
  
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:         sstream << "Severity: high\n"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       sstream << "Severity: medium\n"; break;
    case GL_DEBUG_SEVERITY_LOW:          sstream << "Severity: low\n"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: sstream << "Severity: notification\n"; break;
  }

  LOGGER_ERROR(sstream.str());
}

void Window::cursorPosCallback(GLFWwindow *handle, double xPos, double yPos)
{
  Window *windowPointer = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
  ASSERT(windowPointer, "Could not find window user pointer");

  windowPointer->cursorPosMutex.lock();
  windowPointer->isCursorPosUpdated = true;

  if(windowPointer->mouse.firstMouse)
  {
    windowPointer->mouse.firstMouse = false;
    windowPointer->mouse.x = xPos;
    windowPointer->mouse.y = yPos;
  }
  
  // Update mouse position
  windowPointer->mouse.lastX = windowPointer->mouse.x;
  windowPointer->mouse.lastY = windowPointer->mouse.y;

  // Update mouse last position
  windowPointer->mouse.x = xPos;
  windowPointer->mouse.y = yPos;
  windowPointer->cursorPosMutex.unlock();
}
