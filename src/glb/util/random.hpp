#pragma once

#include <glbpch.hpp>

class Random
{
  public:
  static std::string UUID();
  static int choose(int min, int max);
};