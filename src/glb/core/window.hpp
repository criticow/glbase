#pragma once

#include <glbpch.hpp>
#include <glb/util/logger.hpp>
#include <stb_image.h>

struct Mouse
{
  bool firstMouse = true;
  float x;
  float y;
  float lastX;
  float lastY;
};

class Window
{
  public:
  GLFWwindow *handle = nullptr;
  Mouse mouse;
  int width;
  int height;
  bool isFramebufferUpdated = false;
  bool isCursorPosUpdated = false;
  static std::mutex framebufferMutex;
  static std::mutex cursorPosMutex;

  Window(){};
  Window(int width, int height, const char *title, bool centered = false);
  // Can be used outside main thread
  void loadOpenGL();
  bool isOpen();
  // Can be used outside main thread
  void swapBuffers();
  void pollEvents();
  void waitEvents();
  void destroy();
  void hideCursor();
  // Can be used outside main thread
  void setTitle(const std::string &title);
  void setUserPointer();
  void updateViewport();
  void close();
  void clear();
  void setIcon(const std::string &folder);

  // Callbacks
  static void framebufferSizeCallback(GLFWwindow *handle, int width, int height);
  static void glDebugOutput(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei len, const char *msg, const void *usrParam);
  static void cursorPosCallback(GLFWwindow *handle, double xPos, double yPos);

  private:
  bool isOpenglLoaded = false;
};