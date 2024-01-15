#pragma once

#include <glbpch.hpp>
#include <glb/core/window.hpp>

#define MOUSE_BUTTON_LEFT "button_mouse_left"
#define MOUSE_BUTTON_RIGHT "button_mouse_right"
#define ACTION_LEFT "action_left"
#define ACTION_RIGHT "action_right"
#define ACTION_UP "action_up"
#define ACTION_FORWARD "action_forward"
#define ACTION_BACKWARD "action_backward"
#define ACTION_DOWN "action_down"
#define ACTION_JUMP "action_jump"
#define ACTION_FALL "action_fall"
#define ACTION_ACCEPT "action_accept"
#define ACTION_CANCEL "action_cancel"
#define KEY_F1 "key_f1"
#define KEY_F2 "key_f2"
#define KEY_F3 "key_f3"
#define KEY_F4 "key_f4"
#define KEY_F5 "key_f5"
#define KEY_F6 "key_f6"
#define KEY_F7 "key_f7"
#define KEY_F8 "key_f8"
#define KEY_F9 "key_f9"
#define KEY_F10 "key_f10"
#define KEY_F11 "key_f11"
#define KEY_F12 "key_f12"
#define KEY_ESC "key_esc"

struct Action
{
  struct State
  {
    bool pressed;
    bool held;
    bool released;
  };

  enum Origin
  {
    MOUSE,
    KEYBOARD
  };

  Origin origin;
  State state;
  std::vector<int> keys;
};

class Input
{
  public:
  Input();
  void update(const Window &window);
  bool pressed(const std::string &name);
  bool held(const std::string &name);
  bool released(const std::string &name);

  private:
  std::unordered_map<std::string, Action> actions;
};