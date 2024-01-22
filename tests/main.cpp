#include <glb/glb.hpp>

int main()
{
  Window window(800, 600, "Teste", true);
  window.setUserPointer();
  window.loadOpenGL();
  BaseGUI gui;
  gui.setup(window);


  return 0;
}