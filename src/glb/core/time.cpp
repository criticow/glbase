#include "time.hpp"

Time::Time()
{
  this->deltaTime = 0.0f;
  this->currentTime = 0.0f;
  this->lastTime = 0.0f;
  this->ms = 0.0f;
  this->fps = 0.0f;
  this->deltaTimeSum = 0.0f;
  this->deltaTimeCount = 0;
  this->justUpdated = false;
  this->lastUpdateTime = 0.0f;
  this->updateDelay = 1; // 1 second update delay
}

void Time::update()
{
  this->currentTime = glfwGetTime();
  this->deltaTime = this->currentTime - this->lastTime;
  this->lastTime = this->currentTime;
  this->deltaTimeSum += this->deltaTime;
  this->deltaTimeCount++;
  this->justUpdated = false;

  if(this->currentTime - this->lastUpdateTime >= this->updateDelay)
  {
    this->ms = 1000.0f * (this->deltaTimeSum / this->deltaTimeCount);
    this->fps = 1.0f / (this->deltaTimeSum / this->deltaTimeCount);

    this->deltaTimeSum = 0.0f;
    this->deltaTimeCount = 0;
    this->justUpdated = true;
    this->lastUpdateTime = this->currentTime;
  }
}
