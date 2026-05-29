#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glfw.hpp"
#include "glm.hpp"

class Window
{
    public:
        Window();
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        ~Window() = default;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
        Window& operator=(GLFWwindow* pWindow);

        void makeContextCurrent() const;
        void setInputMode(int mode, int value) const;
        GLFWkeyfun setKeyCallback(GLFWkeyfun callBack) const;
        int shouldClose() const;
        void swapBuffers() const;
        int getKey(int key) const;
        glm::vec2 getCursorPos() const;
    private:
        GLFWwindow* m_pWindow;
};

#endif