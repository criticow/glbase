#pragma once

#include <glbpch.hpp>
#include <glb/util/logger.hpp>

class Temporizer
{
  public:
  float deltaTime;
  float lastTime;
  bool justUpdated;
  float ms;
  float fps;

  Temporizer();
  void update();
  double getTime();
  bool hasPassed(const std::string &name, float milliseconds);

  private:
  std::unordered_map<std::string, float> timeStorage;
  float deltaTimeSum;
  int deltaTimeCount;
  float lastUpdateTime;
  int updateDelay;
  std::chrono::high_resolution_clock::time_point timePoint;
};