#include "input.hpp"

Input::Input()
{
  // Name     |          Origin                 | state | actions / keys
  this->actions = {
    { MOUSE_BUTTON_LEFT, { Action::Origin::MOUSE, {}, { GLFW_MOUSE_BUTTON_LEFT } } },
    { MOUSE_BUTTON_RIGHT, { Action::Origin::MOUSE, {}, { GLFW_MOUSE_BUTTON_RIGHT } } },
    { ACTION_LEFT, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_A, GLFW_KEY_LEFT } } },
    { ACTION_RIGHT, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_D, GLFW_KEY_RIGHT } } },
    { ACTION_FORWARD, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_W, GLFW_KEY_UP } } },
    { ACTION_BACKWARD, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_S, GLFW_KEY_DOWN } } },
    // { ACTION_UP, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_W, GLFW_KEY_UP } } },
    // { ACTION_DOWN, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_S, GLFW_KEY_DOWN } } },
    { ACTION_JUMP, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_SPACE } } },
    { ACTION_FALL, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_LEFT_SHIFT } } },
    { ACTION_ACCEPT, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_ENTER } } },
    { ACTION_CANCEL, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_ESCAPE } } },
    { KEY_F1, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F1 } } },
    { KEY_F2, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F2 } } },
    { KEY_F3, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F3 } } },
    { KEY_F4, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F4 } } },
    { KEY_F5, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F5 } } },
    { KEY_F6, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F6 } } },
    { KEY_F7, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F7 } } },
    { KEY_F8, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F8 } } },
    { KEY_F9, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F9 } } },
    { KEY_F10, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F10 } } },
    { KEY_F11, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F11 } } },
    { KEY_F12, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_F12 } } },
    { KEY_ESC, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_ESCAPE } } },
    { KEY_1, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_1 } } },
    { KEY_2, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_2 } } },
    { KEY_3, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_3 } } },
    { KEY_4, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_4 } } },
    { KEY_5, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_5 } } },
    { KEY_6, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_6 } } },
    { KEY_7, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_7 } } },
    { KEY_8, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_8 } } },
    { KEY_9, { Action::Origin::KEYBOARD, {}, { GLFW_KEY_9 } } },
  };
}

void Input::update(const Window &window)
{
  // Loop through all the set actions to check their current state
  for (auto& [_, action] : this->actions)
  {
    action.state.released = false;

    // Loop through all the keys of the current action, using normal loop to use the current index
    for (size_t i = 0; i < action.keys.size(); i++)
    {
      int key = action.keys[i];

      int state = action.origin == Action::Origin::MOUSE ?
        glfwGetMouseButton(window.handle, key) :
        glfwGetKey(window.handle, key);

      if(state == GLFW_PRESS)
      {
        // This happens on the first time the key is pressed
        if(!action.state.pressed && !action.state.held)
        {
          action.state.pressed = true;
          action.state.held = true;
          action.state.released = false;
        }
        else // this happens if the key is held
        {
          action.state.pressed = false;
          action.state.held = true;
          action.state.released = false;
        }

        break;
      }
      else if(state == GLFW_RELEASE)
      {
        // Doing this for the cases with multiple keys, the first key could be held but the last 
        if(i == action.keys.size() -1)
        {
          if(action.state.pressed || action.state.held)
          {
            action.state.released = true;
          }

          action.state.held = false;
          action.state.pressed = false;
        }
      }
    }
  }
}

bool Input::pressed(const std::string &name)
{
  bool pressed = false;

  // Check if the action exists, if does update the state based on its current state
  if(this->actions.find(name) != this->actions.end())
  {
    pressed = this->actions[name].state.pressed;
  }

  return pressed;
}

bool Input::held(const std::string &name)
{
  bool held = false;

  // Check if the action exists, if does update the state based on its current state
  if(this->actions.find(name) != this->actions.end())
  {
    held = this->actions[name].state.held;
  }

  return held;
}

bool Input::released(const std::string &name)
{
  bool released = false;

  // Check if the action exists, if does update the state based on its current state
  if(this->actions.find(name) != this->actions.end())
  {
    released = this->actions[name].state.released;
  }

  return released;
}
