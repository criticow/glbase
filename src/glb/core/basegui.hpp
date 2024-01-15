#pragma once

#include <glbpch.hpp>

#include <glb/core/window.hpp>
#include <glb/util/logger.hpp>

class BaseGUI
{
  public:
  BaseGUI(){ LOGGER_DEBUG("Created GUI"); };
  void setup(const Window &window);
  void render();
  void destroy();

  private:
  Window *window = nullptr;
  
  protected:
  virtual void update() {};
};
