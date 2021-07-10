#include "header/mainheader.h"
#include "header/_Texture.h"
#include "header/constants.h"

_Texture texture0 = _Texture(TEXTURE_PATH+"Dirt.png");
_Texture texture1 = _Texture(TEXTURE_PATH+"awesomeface.png", GL_RGBA);
_Texture texture2 = _Texture(TEXTURE_PATH+"container2.png", GL_RGBA);
_Texture texture3 = _Texture(TEXTURE_PATH+"container2_specular.png", GL_RGBA);

unsigned int cubeBufferArray;
unsigned int cubeBufferObject;
unsigned int lightSourceVAO;
unsigned int sphereBufferArray;
unsigned int sphereVAO;

int vertNum;
int width, height;

float* SphereVertices;

void InitTexture(){
    texture0.LoadTexture();
    texture1.LoadTexture();
    texture2.LoadTexture();
    texture3.LoadTexture();
}

void InitShader(){
    MainShader = new Shader(SHADER_PATH+"4.vShaderMultipleLights.glsl",SHADER_PATH+"4.fShaderMultipleLights.glsl");
    LightShader = new Shader(SHADER_PATH+"vLightingShader.glsl",SHADER_PATH+"fLightSourceShader.glsl");
    ModelShader = new Shader(SHADER_PATH+"5.vShaderWithMesh.glsl",SHADER_PATH+"5.fShaderWithMesh.glsl");
}

void InitLights(){
    Lights.push_back(Light());
    Lights.push_back(Light());
    Lights.push_back(Light());
    Lights.push_back(Light());

    Lights[0].type = SPOT;
    Lights[0].constant = 1.0;
    Lights[0].linear = 0.14;
    Lights[0].quadratic = 0.07;
    Lights[0].ambient = glm::vec3(.1f,.1f,.1f);
    Lights[0].specular = glm::vec3(1.0f,1.0f,1.0f);
    Lights[0].diffuse = glm::vec3(1,1,1);
    Lights[0].cutOff = glm::cos(glm::radians(12.5f));
    Lights[0].outerCutOff = glm::cos(glm::radians(17.5f));

    Lights[1].type = POINT;
    Lights[1].constant = 1.0;
    Lights[1].linear = 0.14;
    Lights[1].quadratic = 0.07;
    Lights[1].ambient = glm::vec3(.1f,.0f,.0f);
    Lights[1].specular = glm::vec3(1.0f,.0,0);
    Lights[1].diffuse = glm::vec3(1,0,0);
    Lights[1].position = glm::vec3(0.5,0.5,-2);
    Lights[1].modelColor = glm::vec3(1,0,0);

    Lights[2].type = POINT;
    Lights[2].constant = 1.0;
    Lights[2].linear = 0.14;
    Lights[2].quadratic = 0.07;
    Lights[2].ambient = glm::vec3(0,0,0.1f);
    Lights[2].specular = glm::vec3(0,0,1);
    Lights[2].diffuse = glm::vec3(0,0,1);
    Lights[2].position = glm::vec3(0.5,0.5,2);
    Lights[2].modelColor = glm::vec3(0,0,1);

    Lights[3].type = POINT;
    Lights[3].constant = 1.0;
    Lights[3].linear = 0.07;
    Lights[3].quadratic = 0.017;
    Lights[3].ambient = glm::vec3(0.2,0.2,0);
    Lights[3].specular = glm::vec3(1,1,.8);
    Lights[3].diffuse = glm::vec3(1,1,.8);
    Lights[3].position = glm::vec3(2.5,0.5,0);
    Lights[3].modelColor = glm::vec3(1,1,.8);

    for(int i = 0;i<Lights.size();i++){
        Lights[i].AddToShader(MainShader);
        Lights[i].AddToShader(ModelShader);
    }
}

void InitObject(){

    backpack = new Model(MODEL_PATH+"backpack.obj");

    SphereVertices = CreateSphereWithNormal(50,50,.5,&vertNum);
    glGenBuffers(1,&cubeBufferArray);
    glGenBuffers(1,&sphereBufferArray);
    glGenVertexArrays(1,&lightSourceVAO);
    glGenVertexArrays(1,&sphereVAO);
    glGenVertexArrays(1,&cubeBufferObject);

    glBindVertexArray(cubeBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER,cubeBufferArray);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVerticesTexture),cubeVerticesTexture,GL_STATIC_DRAW);
    //vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER,sphereBufferArray);
    glBufferData(GL_ARRAY_BUFFER,vertNum*sizeof(float),SphereVertices,GL_STATIC_DRAW);
    //vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //Light Source Cube
    glBindVertexArray(lightSourceVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeBufferArray);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}

void InitGlfw(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
}