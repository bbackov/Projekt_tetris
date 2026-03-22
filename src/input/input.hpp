#pragma once

#include <GLFW/glfw3.h>
#include <array>

class Input {
public:
    Input();

    void beginFrame();  
    bool pressed(int key) const;
    bool justPressed(int key) const;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    std::array<bool, 512> m_pressed;
    std::array<bool, 512> m_justPressed;
};