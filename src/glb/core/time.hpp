#pragma once

#include <glbpch.hpp>
#include <glb/util/logger.hpp>

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
  bool hasPassed(const std::string &name, float milliseconds);

  private:
  static std::unordered_map<std::string, float> timeStorage;

  float deltaTimeSum;
  int deltaTimeCount;
  float lastUpdateTime;
  int updateDelay;
};