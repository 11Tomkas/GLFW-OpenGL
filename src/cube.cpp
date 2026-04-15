#include "cube.hpp"

#include "glad\gl.h"

Cube::Cube(const VertexBuffer& arrayBuffer)
    : m_vertexArray{}
    , m_position{}
    , m_rotation{}
{
    m_vertexArray.bind();

    arrayBuffer.bind(GL_ARRAY_BUFFER);
    arrayBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));
    arrayBuffer.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(12));
    arrayBuffer.vertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(24));
    arrayBuffer.vertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(36));
    arrayBuffer.unbind(GL_ARRAY_BUFFER);

    m_vertexArray.unbind();
};

void Cube::setPosition(const glm::vec3& position)
{
    m_position = position;
}

void Cube::setRotation(const glm::vec3& rotation)
{
    m_rotation = rotation;
}

const glm::vec3& Cube::position() const
{
    return m_position;
}

const glm::vec3& Cube::rotation() const
{
    return m_rotation;
}

void Cube::draw(const Shader& shader, const MVP& mvp, const Material& material, const Lights& lights)
{
    glActiveTexture(GL_TEXTURE0);
    material.diffuse.bind(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    material.specular.bind(GL_TEXTURE_2D);

    shader.use();
    shader.uniformMatrix4fv("uModel", 1, GL_FALSE, &mvp.model[0][0]);
    shader.uniformMatrix4fv("uView", 1, GL_FALSE, &mvp.view[0][0]);
    shader.uniformMatrix4fv("uProjection", 1, GL_FALSE, &mvp.projection[0][0]);
    shader.uniform1i("uDiffuse", 0);
    shader.uniform1i("uSpecular", 1);
    shader.uniform1f("uShininess", material.shininess);

    shader.uniform3fv("uDirectionLight.direction", 1, &lights.directionLight.direction[0]);
    shader.uniform3fv("uDirectionLight.ambient", 1, &lights.directionLight.ambient[0]);
    shader.uniform3fv("uDirectionLight.diffuse", 1, &lights.directionLight.diffuse[0]);
    shader.uniform3fv("uDirectionLight.specular", 1, &lights.directionLight.specular[0]);

    shader.uniform3fv("uPointLights[0].position", 1, &lights.pointLights[0].position[0]);
    shader.uniform1f("uPointLights[0].constant", lights.pointLights[0].constant);
    shader.uniform1f("uPointLights[0].linear", lights.pointLights[0].linear);
    shader.uniform1f("uPointLights[0].quadratic", lights.pointLights[0].quadratic);
    shader.uniform3fv("uPointLights[0].ambient", 1, &lights.pointLights[0].ambient[0]);
    shader.uniform3fv("uPointLights[0].diffuse", 1, &lights.pointLights[0].diffuse[0]);
    shader.uniform3fv("uPointLights[0].specular", 1, &lights.pointLights[0].specular[0]);

    shader.uniform3fv("uPointLights[1].position", 1, &lights.pointLights[1].position[0]);
    shader.uniform1f("uPointLights[1].constant", lights.pointLights[1].constant);
    shader.uniform1f("uPointLights[1].linear", lights.pointLights[1].linear);
    shader.uniform1f("uPointLights[1].quadratic", lights.pointLights[1].quadratic);
    shader.uniform3fv("uPointLights[1].ambient", 1, &lights.pointLights[1].ambient[0]);
    shader.uniform3fv("uPointLights[1].diffuse", 1, &lights.pointLights[1].diffuse[0]);
    shader.uniform3fv("uPointLights[1].specular", 1, &lights.pointLights[1].specular[0]);

    shader.uniform3fv("uPointLights[2].position", 1, &lights.pointLights[2].position[0]);
    shader.uniform1f("uPointLights[2].constant", lights.pointLights[2].constant);
    shader.uniform1f("uPointLights[2].linear", lights.pointLights[2].linear);
    shader.uniform1f("uPointLights[2].quadratic", lights.pointLights[2].quadratic);
    shader.uniform3fv("uPointLights[2].ambient", 1, &lights.pointLights[2].ambient[0]);
    shader.uniform3fv("uPointLights[2].diffuse", 1, &lights.pointLights[2].diffuse[0]);
    shader.uniform3fv("uPointLights[2].specular", 1, &lights.pointLights[2].specular[0]);

    shader.uniform3fv("uPointLights[3].position", 1, &lights.pointLights[3].position[0]);
    shader.uniform1f("uPointLights[3].constant", lights.pointLights[3].constant);
    shader.uniform1f("uPointLights[3].linear", lights.pointLights[3].linear);
    shader.uniform1f("uPointLights[3].quadratic", lights.pointLights[3].quadratic);
    shader.uniform3fv("uPointLights[3].ambient", 1, &lights.pointLights[3].ambient[0]);
    shader.uniform3fv("uPointLights[3].diffuse", 1, &lights.pointLights[3].diffuse[0]);
    shader.uniform3fv("uPointLights[3].specular", 1, &lights.pointLights[3].specular[0]);

    shader.uniform3fv("uSpotLight.position", 1, &lights.spotLight.position[0]);
    shader.uniform3fv("uSpotLight.direction", 1, &lights.spotLight.direction[0]);
    shader.uniform1f("uSpotLight.innerCutOff", lights.spotLight.innerCutOff);
    shader.uniform1f("uSpotLight.outerCutOff", lights.spotLight.outerCutOff);
    shader.uniform1f("uSpotLight.constant", lights.spotLight.constant);
    shader.uniform1f("uSpotLight.linear", lights.spotLight.linear);
    shader.uniform1f("uSpotLight.quadratic", lights.spotLight.quadratic);
    shader.uniform3fv("uSpotLight.ambient", 1, &lights.spotLight.ambient[0]);
    shader.uniform3fv("uSpotLight.diffuse", 1, &lights.spotLight.diffuse[0]);
    shader.uniform3fv("uSpotLight.specular", 1, &lights.spotLight.specular[0]);

    m_vertexArray.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_vertexArray.unbind();

    shader.unuse();

    material.diffuse.unbind(GL_TEXTURE_2D);
    material.specular.unbind(GL_TEXTURE_2D);
}