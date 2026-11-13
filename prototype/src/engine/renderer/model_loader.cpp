#include "glad/glad.h"

#include <assimp/aabb.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <tinyxml2.h>

#include "engine/renderer/model_loader.hpp"

#include "engine/components/transform.hpp"
#include "engine/components/mesh.hpp"

ModelLoader::ModelLoader(unsigned int shader) {
    shaderProgram = shader;
}

ModelLoader::~ModelLoader() {
    Cleanup();
}

void ModelLoader::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    /*
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_GenNormals);
    */
}


void ModelLoader::SetupMesh(Mesh& mesh) {
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    // Pass vertex position attribute with span and size matching the cube vertex layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Pass vertex normal attribute with span and size matching the cube normal layout
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    modelLoc = glGetUniformLocation(shaderProgram, "u_Model");
    viewLoc = glGetUniformLocation(shaderProgram, "u_View");
    projLoc = glGetUniformLocation(shaderProgram, "u_Projection");

    colorLoc = glGetUniformLocation(shaderProgram, "u_Color");
    lightPosLoc = glGetUniformLocation(shaderProgram, "u_LightPos");
}

void ModelLoader::DrawMesh(Transform& transform, Mesh& mesh) {

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

    glUniform3fv(colorLoc, 1, glm::value_ptr(mesh.color));
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

    glBindVertexArray(mesh.VAO);

    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void ModelLoader::Cleanup() {

}

