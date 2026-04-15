#include "light.hpp"

#include "glad\gl.h"

PointLight::PointLight(const VertexBuffer& arrayBuffer)
    : position{ 0.0f, 0.0f, 0.0f }
    , scale{ 0.0f, 0.0f, 0.0f }
    , constant{ 0.0f }
    , linear{ 0.0f }
    , quadratic{ 0.0f }
    , ambient{ 0.0f, 0.0f, 0.0f }
    , diffuse{ 0.0f, 0.0f, 0.0f }
    , specular{ 0.0f, 0.0f, 0.0f }
    , m_vertexArray{}
{
    m_vertexArray.bind();

    arrayBuffer.bind(GL_ARRAY_BUFFER);
    arrayBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));
    arrayBuffer.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(12));
    arrayBuffer.vertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(24));
    arrayBuffer.vertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(36));
    arrayBuffer.unbind(GL_ARRAY_BUFFER);

    m_vertexArray.unbind();
}

void PointLight::draw(const Shader& shader, const MVP& mvp) const
{
    shader.use();
    shader.uniformMatrix4fv("uModel", 1, GL_FALSE, &mvp.model[0][0]);
    shader.uniformMatrix4fv("uView", 1, GL_FALSE, &mvp.view[0][0]);
    shader.uniformMatrix4fv("uProjection", 1, GL_FALSE, &mvp.projection[0][0]);

    m_vertexArray.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_vertexArray.unbind();

    shader.unuse();
}