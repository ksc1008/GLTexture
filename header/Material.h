#ifndef GLM_MATERIAL_H
#define GLM_MATERIAL_H

#include "glad/glad.h"
#include "Shader.h"
#include "../glm/glm.hpp"

class Material {
private:
    GLuint diffuse;
    GLuint specular;

    glm::vec3 diffuseColor;
    glm::vec3 specularColor;

    bool hasDiffuseMap;
    bool hasSpecularMap;

    float shininess;

public:
    void ApplyToShader(Shader& shader);

    void SetDiffuseColor(float r, float g, float b);
    void SetSpecularColor(float r, float g, float b);
    void SetDiffuseMap(GLuint id);
    void SetSpecularMap(GLuint id);
    void SetShininess(float value);
};


#endif //GLM_MATERIAL_H
