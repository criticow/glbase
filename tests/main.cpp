#include <glb/glb.hpp>

int main()
{
  Window window(800, 600, "Icon", false);
  window.setUserPointer();
  // window.setIcon("data/icons");
  
  while(window.isOpen())
  {
    window.pollEvents();
  }

  window.destroy();
  return 0;
}