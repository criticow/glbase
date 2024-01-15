#pragma once

#include <glbpch.hpp>

class Time
{
  public:
  float deltaTime;
  float currentTime;
  float lastTime;
  bool justUpdated;
  float ms;
  float fps;

  Time();
  void update();
  private:
  float deltaTimeSum;
  int deltaTimeCount;
  float lastUpdateTime;
  int updateDelay;
};