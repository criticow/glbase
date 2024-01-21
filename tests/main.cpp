#include <glb/glb.hpp>

int main()
{
  Window window(800, 600, "Timer", true);
  window.setUserPointer();
  Time time;

  while(window.isOpen())
  {
    window.pollEvents();
    time.update();

    if(time.hasPassed("teste", 1000))
    {
      LOGGER_DEBUG("1 Second passed");
    }
  }

  window.destroy();
  return 0;
}