#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <tinyxml2.h>
#include <string>

#include "engine/components/transform.hpp"
#include "engine/components/mesh.hpp"

class ModelLoader {
    public:
        ModelLoader(unsigned int shader);
        ~ModelLoader();
        void SetupMesh(Mesh& mesh);
        void DrawMesh(Transform& transform, Mesh& mesh);
        void LoadModel(const std::string& path);
    private:
	unsigned int shaderProgram;
        void Cleanup();

        float camRad = 5.0f;
        glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        float camYaw = 0.0f;
        float camPitch = 45.0f;
        glm::vec3 cameraPos = glm::vec3(camRad * std::sin(glm::radians(camYaw)) * std::cos(glm::radians(camPitch)) + camTarget.x,
                                        camRad * std::sin(glm::radians(camPitch)) +
        camTarget.y,
                                        camRad * std::cos(glm::radians(camYaw)) * std::cos(glm::radians(camPitch)) + camTarget.z);
        float fieldOfView = 45.0f;
        glm::vec3 lightPos = glm::vec3(-3.0f, 3.0f, 2.0f);

        glm::mat4 view = glm::lookAt(cameraPos, camTarget, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), 800.0f/600.0f, 0.1f, 100.0f);

        unsigned int modelLoc, viewLoc, projLoc;
        unsigned int colorLoc, lightPosLoc;
};
