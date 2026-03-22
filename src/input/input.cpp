#include "input.hpp"


Input::Input(){
    m_justPressed.fill(false);
    m_pressed.fill(false);
}

void Input::beginFrame(){
    this->m_justPressed.fill(false);
}

bool Input::pressed(int key) const{
    if (key < 0 || key >= 512) return false;
    return this->m_pressed[key];
}

bool Input::justPressed(int key) const {
    if (key < 0 || key >= 512) return false;
    return this->m_justPressed[key];
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key < 0 || key >= 512)
        return;

    Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

    if (!input)
        return;

    if (action == GLFW_PRESS) {
        input->m_pressed[key] = true;
        input->m_justPressed[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        input->m_pressed[key] = false;
    }
}