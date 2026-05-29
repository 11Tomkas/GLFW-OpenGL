#include "delta.hpp"

#include "glfw.hpp"

Delta delta;

Delta::Delta()
    : m_time{ 0.0f }
{
}

void Delta::update()
{
    static float sTimePoint{ static_cast<float>(glfwGetTime()) };
    float timePoint{ static_cast<float>(glfwGetTime()) };

    m_time = timePoint - sTimePoint;

    sTimePoint = timePoint;
}

float Delta::time() const
{
    return m_time;
}