#include "glad/glad.h"
#include <assimp/aabb.h>

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

float vertices[] = {
    // ===== FRONT FACE (Normals +Z) =====
    // Position           // Normals
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 0 (Bottom-Left)
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 1 (Bottom-Right)
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 2 (Top-Right)
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 3 (Top-Left)
    // ===== BACK FACE (Normals -Z) =====
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 4 (Bottom-Left)
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 5 (Bottom-Right)
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 6 (Top-Right)
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 7 (Top-Left)
    // ===== TOP FACE (Normals +Y) =====
    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // Index 8 (Front-Left)
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // Index 9 (Front-Right)
     0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // Index 10 (Back-Right)
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // Index 11 (Back-Left)
    // ===== BOTTOM FACE (Normals -Y) =====
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, // Index 12 (Front-Left)
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, // Index 13 (Front-Right)
     0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, // Index 14 (Back-Left)
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, // Index 15 (Back-Right)
    // ===== RIGHT FACE (Normals +X) =====
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // Index 16 (Back-Bottom)
     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // Index 17 (Back-Top)
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // Index 18 (Front-Top)
     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // Index 19 (Front-Bottom)
    // ===== LEFT FACE (Normals -X) =====
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // Index 20 (Back-Bottom)
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // Index 21 (Back-Top)
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // Index 22 (Front-Top)
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // Index 23 (Front-Bottom)
};

unsigned int indices[] = {
    // FRONT FACE
    0, 1, 2,
    0, 2, 3,
    // BACK FACE
    5, 4, 7,
    5, 7, 6,
    // TOP FACE
    8, 9, 10,
    8, 10, 11,
    // BOTTOM FACE
    12, 13, 14,
    12, 14, 15,
    // RIGHT FACE
    19, 16, 17,
    19, 17, 18,
    // LEFT FACE
    20, 23, 22,
    20, 22, 21
};

float camRad = 5.0f;
glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
float camYaw = 0.0f;
float camPitch = 45.0f;
glm::vec3 cameraPos = glm::vec3(camRad * std::sin(glm::radians(camYaw)) * std::cos(glm::radians(camPitch)) + camTarget.x,
                                camRad * std::sin(glm::radians(camPitch)) +
camTarget.y,
                                camRad * std::cos(glm::radians(camYaw)) * std::cos(glm::radians(camPitch)) + camTarget.z);
float fieldOfView = 45.0f;

glm::vec3 cubeColor = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 lightPos = glm::vec3(-3.0f, 3.0f, 2.0f);

glm::mat4 view = glm::lookAt(cameraPos, camTarget, glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), 800.0f/600.0f, 0.1f, 100.0f);

ModelLoader::ModelLoader(unsigned int shader) {
    shaderProgram = shader;
}

ModelLoader::~ModelLoader() {
    Cleanup();
}

void ModelLoader::DrawMesh(Transform& transform, Mesh& mesh) {
    unsigned int VAO, VBO, EBO;
    unsigned int modelLoc, viewLoc, projLoc;
    unsigned int colorLoc, lightPosLoc;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Pass vertex position attribute with span and size matching the cube vertex layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Pass vertex normal attribute with span and size matching the cube normal layout
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Vertex Shader Uniforms
    modelLoc = glGetUniformLocation(shaderProgram, "u_Model");
    viewLoc = glGetUniformLocation(shaderProgram, "u_View");
    projLoc = glGetUniformLocation(shaderProgram, "u_Projection");

    // Fragment Shader Uniforms
    colorLoc = glGetUniformLocation(shaderProgram, "u_Color");
    lightPosLoc = glGetUniformLocation(shaderProgram, "u_LightPos");
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

void ModelLoader::Cleanup() {

}

