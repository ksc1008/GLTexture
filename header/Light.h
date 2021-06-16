#ifndef GLM_LIGHT_H
#define GLM_LIGHT_H

#include "../glm/glm.hpp"
#include "Shader.h"

enum LightType {SPOT, POINT, DIRECTIONAL};

class Light {
private:

public :
    int _id;
    LightType type;
    glm::vec3 position;
    glm::vec3 direction;

    float outerCutOff;
    float cutOff;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    void ApplyToShader(Shader& shader);
    void AddToShader(Shader* shader);

    void ChangePosition(Shader& shader, glm::vec3 newPos);

    void ChangeDirection(Shader& shader, glm::vec3 newDir);
    void ChangeColor(Shader& shader, glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular);
    void ChangeAttenuation(Shader& shader, float constant, float linear, float quadratic);
    void ChangeCutOff(Shader& shader, float outerCutOff, float cutOff);

};


#endif //GLM_LIGHT_H
