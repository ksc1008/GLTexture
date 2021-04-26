#include "header/MVP.h"
#include "glm/gtc/type_ptr.hpp"

void MVP::SetVertexShaderTransform(unsigned int id) {
    auto viewLoc = glGetUniformLocation(id, "view");
    auto modelLoc = glGetUniformLocation(id, "model");
    auto projectionLoc = glGetUniformLocation(id, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(Projection));
}
