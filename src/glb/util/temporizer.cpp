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