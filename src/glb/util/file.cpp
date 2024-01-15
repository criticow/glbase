#include "file.hpp"

std::string readFile(std::string_view path)
{
  std::ifstream file(path.data());
  ASSERT(file.is_open(), "Could not open file {}", path);

  std::ostringstream sstream;
  sstream << file.rdbuf();
  return sstream.str();
}