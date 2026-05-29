#include "light.hpp"

#include "glad.hpp"

PointLight::PointLight()
    : Cube{}
    , constant{ 0.0f }
    , linear{ 0.0f }
    , quadratic{ 0.0f }
    , ambient{ 0.0f, 0.0f, 0.0f }
    , diffuse{ 0.0f, 0.0f, 0.0f }
    , specular{ 0.0f, 0.0f, 0.0f }
{
}

void PointLight::draw(const Shader& shader, MVP& mvp)
{
    mvp.model = glm::mat4{ 1.0f };
    mvp.model = glm::translate(mvp.model, m_position);
    mvp.model = glm::rotate(mvp.model, m_angle, m_rotationAxis);
    mvp.model = glm::scale(mvp.model, m_scale);

    shader.use();
    shader.uniformMatrix4fv("uModel", 1, GL_FALSE, &mvp.model[0][0]);
    shader.uniformMatrix4fv("uView", 1, GL_FALSE, &mvp.view[0][0]);
    shader.uniformMatrix4fv("uProjection", 1, GL_FALSE, &mvp.projection[0][0]);
    m_vertexArray.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_vertexArray.unbind();
    shader.unuse();
}