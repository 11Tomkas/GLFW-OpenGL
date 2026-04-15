#include "time.hpp"

#include "GLFW\glfw3.h"

Time gTime;

Time::Time()
    : m_delta{ 0.0f }
{
}

void Time::updateDelta()
{
    static float s_time{ static_cast<float>(glfwGetTime()) };
    float time{ static_cast<float>(glfwGetTime()) };

    m_delta = time - s_time;

    s_time = time;
}

float Time::delta()
{
    return m_delta;
}