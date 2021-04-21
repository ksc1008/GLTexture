#ifndef GLM_MVP_H
#define GLM_MVP_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

class MVP {
    glm::mat4 Model = glm::identity<glm::mat4>();
    glm::mat4 View = glm::identity<glm::mat4>();
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f),1.33333f,0.1f,100.0f);

public:
    MVP(){}
    MVP(glm::mat4 model, glm::mat4 view, glm::mat4 proj){Model = model; View = view; Projection = proj;}

    void SetModel(glm::mat4 model){Model = model;}
    void SetView(glm::mat4 view){View = view;}
    void SetPerspective(float fov, float aspect, float near, float far){Projection = glm::perspective(fov,aspect,near,far);}
    void SetOrtho(float left, float right, float bottom, float top, float near, float far){Projection = glm::ortho(left,right,bottom,top,near,far);}
    void SetProjection(glm::mat4 projection){Projection = projection;}

    glm::mat4 GetModelMat(){return Model;}
    glm::mat4 GetViewMat(){return View;}
    glm::mat4 GetProejctoinMat(){return Projection;}
    glm::mat4 GetMVP(){return Projection*View*Model;}
};


#endif //GLM_MVP_H
