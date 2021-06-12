#define STB_IMAGE_IMPLEMENTATION
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#include "Camera.h"
#include "math.h"
#include "header/mainheader.h"
#include "header/Shader.h"
#include "header/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "header/MVP.h"
bool firstMouse = true;
float lastX = WIN_WIDTH;
float lastY = WIN_HEIGHT;

int id;
GLFWwindow* window;
float green;
Shader* ShaderNoColor = nullptr;
Shader* LightingShader = nullptr;
Shader* TextureShader = nullptr;
Shader* LightShader = nullptr;
float Rot=0;
float deltaTime = 0;
float currentFrame = glfwGetTime();
float lastFrame = glfwGetTime();

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
MVP* mvp;
MVP* mvpLight;


float lightX = 0.5;
float lightY = 0.5;
float lightZ = -2;

void MainDisplay(){
    float timeValue = glfwGetTime()*2;
    TextureShader->use();

    glm::vec3 lightPos(lightX, lightY, lightZ);

    //MVP 설정
    mvp->SetView(camera.GetViewMatrix());
    mvpLight->SetView(camera.GetViewMatrix());
    mvp->SetModel(glm::rotate(glm::identity<glm::mat4>(),Rot,glm::vec3(0,1,0)));
    mvp->SetVertexShaderTransform(TextureShader->ID);

    glClearColor(.2f,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Light Mateiral 인자 설정
    TextureShader->setInt("light.enabled",  1);
    TextureShader->setFloat("light.cutOff",  glm::cos(glm::radians(12.5f)));
    TextureShader->setFloat("light.outerCutOff",  glm::cos(glm::radians(17.5f)));
    TextureShader->setVec3("light.direction",  camera.Front);
    TextureShader->setVec3("light.position",  camera.Position);

    TextureShader->setVec3("light.ambient",  0.1f, 0.1f, 0.1f);
    TextureShader->setVec3("light.diffuse",  1, 1, 1); // darken diffuse light a bit
    TextureShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    TextureShader->setFloat("light.constant",1.0);
    TextureShader->setFloat("light.linear",0.14);
    TextureShader->setFloat("light.quadratic",0.07);
    //TextureShader->setVec3("light.position",lightPos);
    TextureShader->setVec3("objectColor",1,1,1);
    TextureShader->setInt("material.diffuse",0);
    TextureShader->setInt("material.specular",1);
    TextureShader->setVec3("material.specular",0.5,0.5,0.5);
    TextureShader->setFloat("material.shininess",25.6);
    TextureShader->setVec3("lightColor",1,1,1);
    TextureShader->setVec3("lightPos",lightPos);
    TextureShader->setVec3("viewPos",camera.Position);

    //Cube Bind
    glBindVertexArray(cubeBufferObject);
    //텍스처 할당
    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glActiveTexture(GL_TEXTURE1);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);


    glBindVertexArray(cubeBufferObject);
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model,glm::vec3(0,-.55,0));
    model = glm::scale(model,glm::vec3(5,.1,5));
    mvp->SetModel(model);
    mvp->SetVertexShaderTransform(TextureShader->ID);

    glActiveTexture(GL_TEXTURE0);
    texture0.Bind();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,0);

    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
    glBindVertexArray(cubeBufferObject);


    model = glm::mat4(1);
    model = glm::translate(model,glm::vec3(1,.3,.3));
    model = glm::scale(model,glm::vec3(.4,.4,.4));
    mvp->SetModel(model);

    LightingShader->use();
    mvp->SetVertexShaderTransform(LightingShader->ID);
    LightingShader->setVec3("objectColor",.8,.8,.8);
    LightingShader->setVec3("material.ambient",0.2125,0.1275,0.054);
    LightingShader->setVec3("material.diffuse",0.714	,0.4284,0.18144);
    LightingShader->setVec3("material.specular",0.6,0.6,0.6);
    LightingShader->setFloat("material.shininess",51.2);
    LightingShader->setVec3("lightColor",1,1,1);
    LightingShader->setVec3("lightPos",lightPos);
    LightingShader->setVec3("viewPos",camera.Position);

    glBindVertexArray(sphereVAO);
    glDrawArrays(GL_TRIANGLES,0,vertNum);
    glBindVertexArray(0);;

    glm::mat4 trans = glm::identity<glm::mat4>();
    trans = glm::translate(trans,lightPos);
    trans = glm::scale(trans,glm::vec3(.2));
    mvpLight->SetModel(trans);
    LightShader->use();

    mvpLight->SetVertexShaderTransform(LightShader->ID);

    glBindVertexArray(lightSourceVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);




    glfwSwapBuffers(window);
    glfwPollEvents();
}

void processInput(GLFWwindow *_window)
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);


    if (glfwGetKey(_window, GLFW_KEY_K) == GLFW_PRESS)
        lightX-=deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_U) == GLFW_PRESS)
        lightZ+=deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_J) == GLFW_PRESS)
        lightZ-=deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_H) == GLFW_PRESS)
        lightX+=deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_Y) == GLFW_PRESS)
        lightY+=deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_I) == GLFW_PRESS)
        lightY-=deltaTime;
}

// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(int argc, char**argv) {
    mvp = new MVP();
    mvpLight = new MVP();
    stbi__vertically_flip_on_load =true;
    InitGlfw();
    window = glfwCreateWindow(WIN_WIDTH,WIN_HEIGHT,"HAHA",NULL,NULL);
    if(window == NULL){
        std::cout <<"OOPS"<<"\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    InitShader();
    InitTexture();
    InitObject();
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1280, 720);
    mvp->SetPerspective(glm::radians(45.0f),16.0f/9.0f,0.1f,100.0f);
    mvpLight->SetPerspective(glm::radians(45.0f),16.0f/9.0f,0.1f,100.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
    mvp->SetView(view);
    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        InputEvent( window);
        MainDisplay();
    }
    glfwTerminate();
    return 0;
}
