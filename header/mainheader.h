#ifndef GLTEXTURE_MAINHEADER_H
#define GLTEXTURE_MAINHEADER_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Texture.h"
#include "Shader.h"

void InitGlfw();
void InitLight();
extern Texture texture0;
extern Texture texture1;
extern float deltaTime;
extern float Rot;
extern unsigned int cubeBufferArray;
extern unsigned int cubeBufferObject;
extern unsigned int lightSourceVAO;

extern void InputEvent(GLFWwindow* window);
void InitShader();
void InitObject();
void InitTexture();

extern Shader* ShaderNoColor;
extern Shader* LightingShader;
extern Shader* LightShader;
#endif //GLTEXTURE_MAINHEADER_H
