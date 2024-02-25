#include "temporizer.hpp"

Temporizer::Temporizer()
{
  this->timePoint = std::chrono::high_resolution_clock::now();
  this->deltaTime = 0.0f;
  this->lastTime = 0.0f;
  this->ms = 0.0f;
  this->fps = 0.0f;
  this->deltaTimeSum = 0.0f;
  this->deltaTimeCount = 0;
  this->justUpdated = false;
  this->lastUpdateTime = 0.0f;
  this->updateDelay = 1; // 1 second update delay
}

void Temporizer::update()
{
  this->deltaTime = this->getTime() - this->lastTime;
  this->lastTime = this->getTime();
  this->deltaTimeSum += this->deltaTime;
  this->deltaTimeCount++;
  this->justUpdated = false;

  if(this->getTime() - this->lastUpdateTime >= this->updateDelay)
  {
    this->ms = 1000.0f * (this->deltaTimeSum / this->deltaTimeCount);
    this->fps = 1.0f / (this->deltaTimeSum / this->deltaTimeCount);

    this->deltaTimeSum = 0.0f;
    this->deltaTimeCount = 0;
    this->justUpdated = true;
    this->lastUpdateTime = this->getTime();
  }
}

double Temporizer::getTime()
{
  auto end = std::chrono::high_resolution_clock::now();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - this->timePoint);
  // Seconds
  return static_cast<double>(millis.count() / 1000.0f);
}

bool Temporizer::hasPassed(const std::string &name, float milliseconds)
{
  // There is no register of the starting time in the storage
  if(this->timeStorage.find(name) == this->timeStorage.end())
  {
    this->timeStorage[name] = this->getTime();
  }

  // The amount expected to pass have passed
  if((this->getTime() - this->timeStorage[name]) * 1000 >= milliseconds)
  {
    // Set the starting time in the storage
    this->timeStorage[name] = this->getTime();
    return true;
  }

  return false;
}

void Temporizer::clearTimepoint(const std::string &name)
{
  this->timeStorage.erase(name);
}

void Temporizer::setCooldown(const std::string &name, float milliseconds)
{
  // Saving the cooldown time
  this->cooldownStorage[name + "_cooldown"] = milliseconds;
  // Saving the starting point of the cooldown
  this->timeStorage[name + "_cooldown"] = this->getTime();
}

float Temporizer::getCooldown(const std::string &name)
{
  // Check if there is a cd already, if not create one with 0 cd
  if(this->cooldownStorage.find(name + "_cooldown") == this->cooldownStorage.end())
  {
    // Saving the cooldown time
    this->cooldownStorage[name + "_cooldown"] = 0;
    // Saving the starting point of the cooldown
    this->timeStorage[name + "_cooldown"] = this->getTime();
  }

  float cdTime = this->cooldownStorage[name + "_cooldown"];
  float cdTimePoint = this->timeStorage[name + "_cooldown"];
  float remainingTime = (this->getTime() - cdTimePoint) * 1000.0f - cdTime;
  return remainingTime < 0.0f ? remainingTime : 0.0f;
}

bool Temporizer::isOnCooldown(const std::string &name)
{
  bool res = true;

  // Check if there is a cd already, if not create one with 0 cd
  if(this->cooldownStorage.find(name + "_cooldown") == this->cooldownStorage.end())
  {
    // Saving the cooldown time
    this->cooldownStorage[name + "_cooldown"] = 0;
    // Saving the starting point of the cooldown
    this->timeStorage[name + "_cooldown"] = this->getTime();
  }

  float cdTime = this->cooldownStorage[name + "_cooldown"];
  float cdTimePoint = this->timeStorage[name + "_cooldown"];

  // Check if the cooldown time has passed
  if((this->getTime() - cdTimePoint) * 1000 >= cdTime)
  {
    res = false;
  }

  return res;
}
