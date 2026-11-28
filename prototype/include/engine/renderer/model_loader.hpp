#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <string>

#include "engine/components/camera.hpp"
#include "engine/components/transform.hpp"
#include "engine/components/mesh.hpp"

class ModelLoader {
    public:
        ModelLoader(unsigned int shader);
        ~ModelLoader();
        void SetupMesh(Mesh& mesh);
        void DrawMesh(Transform& transform, Mesh& mesh, const Camera& camera);
        void LoadModel(const std::string& path);
    private:
	unsigned int shaderProgram;
        void Cleanup();

        glm::vec3 lightPos = glm::vec3(-3.0f, 3.0f, 2.0f);

        unsigned int modelLoc, viewLoc, projLoc;
        unsigned int colorLoc, lightPosLoc;
};
