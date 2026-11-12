#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <tinyxml2.h>

#include "engine/components/transform.hpp"
#include "engine/components/mesh.hpp"

class ModelLoader {
    public:
        ModelLoader(unsigned int shader);
        ~ModelLoader();
        void DrawMesh(Transform& transform, Mesh& mesh);
    private:
	unsigned int shaderProgram;
        void Cleanup();
};
