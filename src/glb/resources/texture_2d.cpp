#include "texture_2d.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D::Texture2D(const char *path)
{
  glGenTextures(1, &this->handle);
  glBindTexture(GL_TEXTURE_2D, this->handle);

  int width, height, channels;
  unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

  ASSERT(data, "Could not load texture {}", path);

  GLenum format;

  if(channels == 1) { format = GL_RED; }
  else if(channels == 3) { format = GL_RGB; }
  else { format = GL_RGBA; }

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(data);
}

Texture2D::Texture2D(GLsizei width, GLsizei height)
{
  glGenTextures(1, &this->handle);
  glBindTexture(GL_TEXTURE_2D, this->handle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &glm::vec3(1.0f)[0]);
}

void Texture2D::bind(GLenum position)
{
  glActiveTexture(position);
  glBindTexture(GL_TEXTURE_2D, this->handle);
}

void Texture2D::destroy()
{
  glDeleteTextures(1, &this->handle);
}
