#include "header/Material.h"

void Material::ApplyToShader(Shader &shader) {
    if(hasDiffuseMap){
        shader.setBool("material.hasDiffuseMap",true);
        shader.setInt("material.diffuse",diffuse);
    }
    else{
        shader.setBool("material.hasDiffuseMap",false);
        shader.setVec3("material.diffuseColor",diffuseColor);
    }

    if(hasSpecularMap){
        shader.setBool("material.hasSpecularMap",true);
        shader.setInt("material.specular",specular);
    }
    else{
        shader.setBool("material.hasSpecularMap",false);
        shader.setVec3("material.specularColor",specularColor);
    }

    shader.setFloat("material.shininess",shininess);
}

void Material::SetDiffuseColor(float r, float g, float b) {
    hasDiffuseMap = false;
    diffuseColor = glm::vec3(r,g,b);
}

void Material::SetSpecularColor(float r, float g, float b) {
    hasSpecularMap = false;
    specularColor = glm::vec3(r,g,b);

}

void Material::SetSpecularMap(GLuint id) {
    hasSpecularMap = true;
    specular = id;
}

void Material::SetDiffuseMap(GLuint id) {
    hasDiffuseMap = true;
    diffuse = id;
}

void Material::SetShininess(float value) {
    shininess = value;
}
