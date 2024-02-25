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

  Temporizer tempo;
  bool it = true;
  
  while(window.isOpen())
  {
    tempo.update();

    if(it)
    {
      it = false;
      tempo.setCooldown("myCd", 5000);
    }

    if(!tempo.isOnCooldown("myCd"))
    {
      std::cout << "CD ended" << std::endl;
    }

    window.pollEvents();
    window.clear();
    gui.render();
    window.swapBuffers();
  }

  window.destroy();
  return 0;
}