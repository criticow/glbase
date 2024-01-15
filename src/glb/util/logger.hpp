#pragma once

#include <glbpch.hpp>

namespace nel
{
  class Logger
  {
    public:
    template <typename... Args>
    void debug(Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::cout << "[\033[36mDBG\033[0m]: " << buffer << std::endl;
    }

    template <typename... Args>
    void warn(Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::cout << "[\033[33mWRN\033[0m]: " << buffer << std::endl;
    }

    template <typename... Args>
    void error(const char *file, int line, Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::string cppFile = std::string(file);
      cppFile = cppFile.substr(cppFile.find_last_of("\\") + 1);
      std::cout << "[\033[31mERR\033[0m][\033[34m" << cppFile << ":" << line << "\033[0m]: " << buffer << std::endl;
    }

    template <typename... Args>
    void critical(const char *file, int line, Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::string cppFile = std::string(file);
      cppFile = cppFile.substr(cppFile.find_last_of("\\") + 1);
      std::cout << "[\033[41m\033[37mCRT\033[0m][\033[34m"<< cppFile << ":" << line << "\033[0m]: " << buffer << std::endl;
    }

    private:
    std::string buffer = "";

    void log(const auto &fmt)
    {
      std::ostringstream sstream;
      sstream << fmt;
      buffer = sstream.str();
    }

    template<typename... Args>
    void log(const std::string &fmt, Args... args)
    {
      buffer = fmt;
      size_t index = 0;
      // Replace recursively
      ((replace(index++, args)), ...);
    }

    template <typename T>
    void replace(size_t index, T value)
    {
      std::ostringstream sstream;
      if(std::is_same<T, bool>::value)
      {
        sstream << std::boolalpha << value;
      }
      else
      {
        sstream << value;
      }

      // Not indexed replacements
      size_t pos = buffer.find("{}");
      if(pos != std::string::npos)
      {
        buffer.replace(pos, 2, sstream.str());
      }

      // Indexed replacement
      pos = buffer.find("{" + std::to_string(index) + "}");
      while(pos != std::string::npos)
      {
        buffer.replace(pos, 3, sstream.str());
        pos = buffer.find("{" + std::to_string(index) + "}");
      }
    }
  };

  inline Logger logger;
};

#ifdef LOGGER_GLM_EXT

std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec2)
{
  os << "(" << vec2.x << ", " << vec2.y << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec3)
{
  os << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec4)
{
  os << "(" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::mat4 &mat4)
{
  for(int i = 0; i < 4; i++)
  {
    os << "[ ";
    for(int j = 0; j < 4; j++)
    {
      os << mat4[i][j] << (j < 3 ? ",\t" : "");
    }
    os << " ]";
  }
  return os;
}

#endif

#ifdef LOGGER_BULLET3_EXT

std::ostream &operator<<(std::ostream &os, const btVector3 &vec3)
{
  os << "(" << vec3.x() << ", " << vec3.y() << ", " << vec3.z() << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const btQuaternion &quat)
{
  os << "(" << quat.x() << ", " << quat.y() << ", " << quat.z() << ", " << quat.w() << ")";
  return os;
}

#endif

#ifdef NDEBUG

#define LOGGER_DEBUG(...) do { } while(0)
#define LOGGER_WARN(...) do { } while(0)
#define LOGGER_ERROR(...) do { } while(0)
#define LOGGER_CRITICAL(...) do { } while(0)
#define ASSERT(condition, ...) if(condition) { do { } while(0); }

#else

#if defined(_MSC_VER)
  // For Visual Studio
  #define DEBUG_BREAK __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
  // For GCC and Clang
  #define DEBUG_BREAK __builtin_trap()
#else
  // For other compilers/platforms, you may need to adapt
  #error "Unsupported compiler/platform for DEBUG_BREAK"
#endif

#define LOGGER_DEBUG(...) nel::logger.debug(__VA_ARGS__)
#define LOGGER_WARN(...) nel::logger.warn(__VA_ARGS__)
#define LOGGER_ERROR(...) nel::logger.error(__FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_CRITICAL(...) nel::logger.critical(__FILE__, __LINE__, __VA_ARGS__)
// #define ASSERT(condition, ...) if(!condition) { nel::logger.critical(__FILE__, __LINE__, __VA_ARGS__); DEBUG_BREAK(); }
#define ASSERT(condition, ...) \
  if (!(condition)) { \
    nel::logger.critical(__FILE__, __LINE__, __VA_ARGS__); \
    DEBUG_BREAK; \
  }

#endif