#ifndef GLTEXTURE_MAINHEADER_H
#define GLTEXTURE_MAINHEADER_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"

void InitGlfw();
extern Texture texture0;
extern Texture texture2;
extern Texture texture1;
extern Texture texture3;
extern double deltaTime;
extern float Rot;
extern unsigned int cubeBufferArray;
extern unsigned int sphereBufferArray;
extern unsigned int cubeBufferObject;
extern unsigned int lightSourceVAO;
extern unsigned int sphereVAO;

extern int vertNum;

extern void InputEvent(GLFWwindow* window);
void InitShader();
void InitObject();
void InitTexture();
void InitLights();
extern float* CreateSphere(int stack, int slice, float radius,int* vertexNum);
extern float* CreateSphereWithNormal(int stack, int slice, float radius,int* vertexNum);
extern Shader* ShaderNoColor;
extern Shader* LightingShader;
extern Shader* LightShader;
extern Shader* TextureShader;
extern Shader* MainShader;

extern Light* FlashLight;
extern Light* PointLight0;
extern Light* PointLight1;
extern Light* PointLight2;
extern Light* DirectionalLight;

extern float cubeVerticesNormal[216];
extern float cubeVerticesTexture[288];
extern float cubeVertices[180];
#endif //GLTEXTURE_MAINHEADER_H
