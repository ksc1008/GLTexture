#define STB_IMAGE_IMPLEMENTATION
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#include "Camera.h"
#include "math.h"
#include "header/mainheader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "header/Material.h"
#include "header/MVP.h"

bool firstMouse = true;
double lastX = WIN_WIDTH;
double lastY = WIN_HEIGHT;

GLFWwindow* window;
Shader* MainShader;
Shader* LightShader;
Shader* ModelShader;
Model* backpack;
float Rot=0;
double deltaTime = 0;
double currentFrame;
double lastFrame;

Camera camera;
MVP* mvp;
MVP* mvpLight;

Material* containerMat;
Material* sphereMat;

std::vector<Light>Lights;

double lightX;
double lightY;
double lightZ;

void MainDisplay(){
    //double timeValue = glfwGetTime()*2;
    MainShader->use();
    MainShader->setVec3("objectColor",1,1,1);

    glm::vec3 lightPos(lightX, lightY, lightZ);

    //MVP 설정
    mvp->SetView(camera.GetViewMatrix());
    mvpLight->SetView(camera.GetViewMatrix());
    mvp->SetModel(glm::rotate(glm::identity<glm::mat4>(),Rot,glm::vec3(0,1,0)));
    mvp->SetVertexShaderTransform(MainShader->ID);

    glClearColor(.2f,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Lights[0].direction = camera.Front;
    Lights[0].position = camera.Position;
    for(int i = 0;i<Lights.size();i++) {
        Lights[i].ApplyToShader(*MainShader);
    }
    /*###############################################
      ##################Light Setting################
      ###############################################*/
    MainShader->setInt("directionalNum",MainShader->DirectionalNum);
    MainShader->setInt("pointNum",MainShader->PointNum);
    MainShader->setInt("spotNum",MainShader->SpotNum);
    MainShader->setVec3("viewPos",camera.Position);

    /*###############################################
      ###################Container###################
      ###############################################*/

    glBindVertexArray(cubeBufferObject);
    containerMat->ApplyToShader(*MainShader);
    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glActiveTexture(GL_TEXTURE1);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);

    /*###############################################
      #####################Floor#####################
      ###############################################*/

    glBindVertexArray(cubeBufferObject);
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model,glm::vec3(0,-.55,0));
    model = glm::scale(model,glm::vec3(5,.1,5));
    mvp->SetModel(model);
    mvp->SetVertexShaderTransform(MainShader->ID);
    glActiveTexture(GL_TEXTURE0);
    texture0.Bind();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,0);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);

    /*###############################################
      ####################Sphere#####################
      ###############################################*/

    model = glm::mat4(1);
    model = glm::translate(model,glm::vec3(1,.3,-1.3));
    model = glm::scale(model,glm::vec3(.5));
    mvp->SetModel(model);
    mvp->SetVertexShaderTransform(MainShader->ID);
    sphereMat->ApplyToShader(*MainShader);
    glBindVertexArray(sphereVAO);
    glDrawArrays(GL_TRIANGLES,0,vertNum);
    glBindVertexArray(0);

    ModelShader->use();

    for(int i = 0;i<Lights.size();i++) {
        Lights[i].ApplyToShader(*ModelShader);
    }

    model = glm::mat4(1);
    model = glm::translate(model,glm::vec3(1.2,.3,0));
    model = glm::scale(model,glm::vec3(.3));

    mvp->SetModel(model);
    mvp->SetVertexShaderTransform(ModelShader->ID);
    ModelShader->setVec3("viewPos",camera.Position);
    ModelShader->setInt("directionalNum",ModelShader->DirectionalNum);
    ModelShader->setFloat("material.shininess",32.0);
    ModelShader->setInt("pointNum",ModelShader->PointNum);
    ModelShader->setInt("spotNum",ModelShader->SpotNum);
    backpack->Draw(*ModelShader);

    LightShader->use();
    for(int i = 0;i<Lights.size();i++){
        Lights[i].Draw(*LightShader,lightSourceVAO,*mvp);
    }

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
}

// -------------------------------------------------------
void mouse_callback(GLFWwindow* _window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* _window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(int argc, char**argv) {
    currentFrame = glfwGetTime();
    lastFrame = glfwGetTime();
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    mvp = new MVP();
    mvpLight = new MVP();
    //stbi__vertically_flip_on_load =true;
    InitGlfw();
    window = glfwCreateWindow(WIN_WIDTH,WIN_HEIGHT,"HAHA",nullptr,nullptr);
    if(window == nullptr){
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
    InitLights();
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1280, 720);
    mvp->SetPerspective(glm::radians(45.0f),16.0f/9.0f,0.1f,100.0f);
    mvpLight->SetPerspective(glm::radians(45.0f),16.0f/9.0f,0.1f,100.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glm::mat4 view = glm::mat4(1.0f);

    sphereMat = new Material();
    containerMat = new Material();

    sphereMat->SetDiffuseColor(0.8,0.8,0.2);
    sphereMat->SetSpecularColor(1,1,1);
    sphereMat->SetShininess(100);

    containerMat->SetDiffuseMap(0);
    containerMat->SetSpecularMap(1);
    containerMat->SetShininess(25.6f);

    backpack = new Model("models/backpack.obj");

    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        InputEvent(window);
        MainDisplay();
    }
    glfwTerminate();
    return 0;
}
