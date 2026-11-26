#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <iterator>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * Moved the cube data here, I don't know
 * if you want to add more generic shape 
 * data data here e.g pyramid, sphere etc.
 * Also you may need to add a helper funciton
 * to your Mesh struct to allow the user to 
 * select a specfic mesh type to render
 * 
 * - Isaiah P.
 */


// Cube Data
const float cubeVertices[] = {
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
const unsigned int cubeIndices[] = {
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

inline const std::vector<float> cubeVertexList(std::begin(cubeVertices), std::end(cubeVertices));
inline const std::vector<unsigned char> cubeIndexList(std::begin(cubeIndices), std::end(cubeIndices));

struct Mesh {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 color;

    unsigned int VAO, VBO, EBO;
};
