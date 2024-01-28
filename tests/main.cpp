#include <glb/glb.hpp>
#include "GUI.hpp"

int main()
{
  Window window(800, 600, "Icon", false);
  window.setUserPointer();
  window.loadOpenGL();
  GUI gui;
  gui.setup(window);
  // window.setIcon("data/icons");
  
  while(window.isOpen())
  {
    window.pollEvents();
    window.clear();
    gui.render();
    window.swapBuffers();
  }

  window.destroy();
  return 0;
}