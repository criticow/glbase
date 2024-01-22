#include <glb/glb.hpp>

int main()
{
  Temporizer tempo;
  while(true)
  {
    if(tempo.hasPassed("teste", 1000))
    {
      LOGGER_DEBUG("1 second passed");
    }
  }
  return 0;
}