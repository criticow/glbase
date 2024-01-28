#pragma once

#include <glb/glb.hpp>

// Define your tabs
enum Tabs {
    Tab_1,
    Tab_2,
    Tab_3,
    // Add more tabs as needed
    Tab_Count
};

// Variable to keep track of the current tab
Tabs currentTab = Tab_1;

class GUI : public BaseGUI
{
  public:
    virtual void renderUI()
    { 
      ImGui::Begin("Hello");
      if (ImGui::BeginTabBar("Tabs")) {
        if (ImGui::BeginTabItem("Tab 1")) {
          // Render content for Tab 1
          ImGui::Text("This is the content of Tab 1");
          ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Tab 2")) {
          // Render content for Tab 2
          ImGui::Text("This is the content of Tab 2");
          ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Tab 3")) {
          // Render content for Tab 3
          ImGui::Text("This is the content of Tab 3");
          ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
      }

      // Change the current tab programmatically
      if (ImGui::Button("Switch to Tab 2")) {
        currentTab = Tab_2;
      }

      if (ImGui::Button("Switch to Tab 3")) {
        currentTab = Tab_3;
      }
      ImGui::End();
    };
    void update()
    {

    }
};