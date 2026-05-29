#include "window.hpp"

Window::Window()
    : m_pWindow{ nullptr }
{
}

Window& Window::operator=(GLFWwindow* pWindow)
{
    m_pWindow = pWindow;

    return *this;
}

void Window::makeContextCurrent() const
{
    glfwMakeContextCurrent(m_pWindow);
}

void Window::setInputMode(int mode, int value) const
{
    glfwSetInputMode(m_pWindow, mode, value);
}

GLFWkeyfun Window::setKeyCallback(GLFWkeyfun callBack) const
{
    return glfwSetKeyCallback(m_pWindow, callBack);
}

int Window::shouldClose() const
{
    return glfwWindowShouldClose(m_pWindow);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(m_pWindow);
}

int Window::getKey(int key) const
{
    return glfwGetKey(m_pWindow, key);
}

glm::vec2 Window::getCursorPos() const
{
    glm::dvec2 cursorPos;

    glfwGetCursorPos(m_pWindow, &cursorPos.x, &cursorPos.y);

    return static_cast<glm::vec2>(cursorPos);
}