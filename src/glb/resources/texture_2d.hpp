#pragma once

#include <glbpch.hpp>
#include <glb/util/logger.hpp>

class Texture2D
{
  public:
  GLuint handle;
  Texture2D(){};
  Texture2D(const char *path);
  // Shadow Map texture
  Texture2D(GLsizei width, GLsizei height);
  void bind(GLenum position = GL_TEXTURE0);
  void destroy();
};