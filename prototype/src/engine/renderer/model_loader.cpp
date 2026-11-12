#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <tinyxml2.h>

#include "engine/renderer/model_loader.hpp"

#include "engine/components/transform.hpp"
#include "engine/components/mesh.hpp"

glm::mat4 view = glm::lookAt(cameraPos, camTarget, glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), aspect, 0.1f, 100.0f);

ModelLoader::ModelLoader() {
}

ModelLoader::~ModelLoader() {
    cleanup();
}

void ModelLoader::DrawModels(Transform& transform, Mesh& mesh) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform.xPos, transform.yPos, transform.zPos));
    model = glm::rotate(model, glm::radians(transform.xRot), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.yRot), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.zRot), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(transform.xScale, transform.yScale, transform.zScale));

    // Push matrices to shader
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glUniform3fv(colorLoc, 1, glm::value_ptr(cubeColor));
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
}

void ModelLoader::cleanup() {

}

