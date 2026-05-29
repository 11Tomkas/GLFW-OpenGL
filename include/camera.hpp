#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm.hpp"
#include "window.hpp"

class Camera
{
    public:
        Camera();
        Camera(const Camera&) = delete;
        Camera(Camera&&) = delete;
        ~Camera() = default;
        Camera& operator=(const Camera&) = delete;
        Camera& operator=(Camera&&) = delete;

        void update(const Window& window);
        void updatePosition(const Window& window);
        void updateFront(const Window& window);
        const glm::vec3& position() const;
        const glm::vec3& front() const;
        const glm::mat4& view() const;
    private:
        glm::vec3 m_position;
        glm::vec3 m_right;
        glm::vec3 m_up;
        glm::vec3 m_front;
        glm::vec3 m_worldUp;
        float m_yaw;
        float m_pitch;
        glm::mat4 m_view;
};

#endif