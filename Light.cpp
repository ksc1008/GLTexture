#include "header/Light.h"
#include <string>

const char* GetParam(LightType type, std::string str, int ID){
    std::string s;
    switch(type){
        case SPOT:
            s ="spotLights[" + std::to_string(ID) + "].";
            break;
        case POINT:
            s ="pointLights[" + std::to_string(ID) + "].";
            break;
        case DIRECTIONAL:
            s ="directionalLights[" + std::to_string(ID) + "].";
            break;
    }
    s= s+str;
    return s.c_str();
}

void Light::ApplyToShader(Shader &shader) {
    shader.setVec3(GetParam(type,"ambient",_id),ambient);
    shader.setVec3(GetParam(type,"diffuse",_id),diffuse);
    shader.setVec3(GetParam(type,"specular",_id),specular);
    switch(type){
        case SPOT:
            shader.setVec3(GetParam(type,"position",_id),position);
            shader.setVec3(GetParam(type,"direction",_id),direction);
            shader.setFloat(GetParam(type,"constant",_id),constant);
            shader.setFloat(GetParam(type,"linear",_id),linear);
            shader.setFloat(GetParam(type,"quadratic",_id),quadratic);
            shader.setFloat(GetParam(type,"cutOff",_id),cutOff);
            shader.setFloat(GetParam(type,"outerCutOff",_id),outerCutOff);
            break;
        case POINT:
            shader.setVec3(GetParam(type,"position",_id),position);

            shader.setFloat(GetParam(type,"constant",_id),constant);
            shader.setFloat(GetParam(type,"linear",_id),linear);
            shader.setFloat(GetParam(type,"quadratic",_id),quadratic);

            break;
        case DIRECTIONAL:
            shader.setVec3(GetParam(type,"direction",_id),direction);
            break;
    }
}

void Light::AddToShader(Shader *shader) {
    int id;
    switch (type) {
        case SPOT:
            id = shader->SpotNum++;
            shader->setInt("spotNum",shader->SpotNum);
            break;
        case POINT:
            id = shader->PointNum++;
            shader->setInt("pointNum",shader->PointNum);
            break;
        case DIRECTIONAL:
            id = shader->DirectionalNum++;
            shader->setInt("directionalNum",shader->DirectionalNum);
            break;
    }
    this->_id = id;
    ApplyToShader(*shader);
}

void Light::ChangePosition(Shader& shader, glm::vec3 newPos) {
    shader.setVec3(GetParam(type,"position",_id),newPos);
    position = newPos;
}

void Light::ChangeDirection(Shader& shader, glm::vec3 newDir) {
    shader.setVec3(GetParam(type,"direction",_id),newDir);
    direction = newDir;
}

void Light::ChangeColor(Shader& shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
    shader.setVec3(GetParam(type,"ambient",_id),_ambient);
    shader.setVec3(GetParam(type,"diffuse",_id),_diffuse);
    shader.setVec3(GetParam(type,"specular",_id),_specular);

    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
}

void Light::ChangeAttenuation(Shader& shader, float _constant, float _linear, float _quadratic) {
    shader.setFloat(GetParam(type,"constant",_id),_constant);
    shader.setFloat(GetParam(type,"linear",_id),_linear);
    shader.setFloat(GetParam(type,"quadratic",_id),_quadratic);

    constant = _constant;
    linear = _linear;
    quadratic = _quadratic;
}

void Light::ChangeCutOff(Shader& shader, float _outerCutOff, float _cutOff) {
    shader.setFloat(GetParam(type,"position",_id),_cutOff);
    cutOff = _cutOff;
}
