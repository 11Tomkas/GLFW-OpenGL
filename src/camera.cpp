#include "camera.hpp"

#include "delta.hpp"

Camera::Camera()
    : m_position{ 0.0f, 0.0f, 0.0f }
    , m_right{ 1.0f, 0.0f, 0.0f }
    , m_up{ 0.0f, 1.0f, 0.0f }
    , m_front{ 0.0f, 0.0f, -1.0f }
    , m_worldUp{ 0.0f, 1.0f, 0.0f }
    , m_yaw{ -90.0f }
    , m_pitch{ 0.0f }
    , m_view{ glm::lookAt(m_position, (m_position + m_front), m_up) }
{
}

void Camera::update(const Window& window)
{
    updatePosition(window);
    updateFront(window);
}

void Camera::updatePosition(const Window& window)
{
    if (window.getKey(GLFW_KEY_A))
        m_position -= m_right * 2.0f * delta.time();
    else
    if (window.getKey(GLFW_KEY_D))
        m_position += m_right * 2.0f * delta.time();

    if (window.getKey(GLFW_KEY_W))
        m_position += m_front * 2.0f * delta.time();
    else
    if (window.getKey(GLFW_KEY_S))
        m_position -= m_front * 2.0f * delta.time();

    if (window.getKey(GLFW_KEY_A) || window.getKey(GLFW_KEY_D) || window.getKey(GLFW_KEY_W) || window.getKey(GLFW_KEY_S))
        m_view = glm::lookAt(m_position, (m_position + m_front), m_up);
}

void Camera::updateFront(const Window& window)
{
    static glm::vec2 sCursorPos{ window.getCursorPos() };
    glm::vec2 cursorPos{ window.getCursorPos() };

    if (sCursorPos != cursorPos)
    {
        glm::vec2 cursorOffset{ cursorPos - sCursorPos };

        m_yaw += cursorOffset.x * 2.0f * delta.time();
        m_pitch += -cursorOffset.y * 2.0f * delta.time();

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        else
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        m_front.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
        m_front.y = glm::sin(glm::radians(m_pitch));
        m_front.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
        m_front = glm::normalize(m_front);
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
        m_view = glm::lookAt(m_position, (m_position + m_front), m_up);

        sCursorPos = cursorPos;
    }
}

const glm::vec3& Camera::position() const
{
    return m_position;
}

const glm::vec3& Camera::front() const
{
    return m_front;
}

const glm::mat4& Camera::view() const
{
    return m_view;
}