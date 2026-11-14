#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Mesh {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 color;

    unsigned int VAO, VBO, EBO;
};
