#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <tinyxml2.h>

class ModelLoader {
    public:
        ModelLoader();
        ~ModelLoader();
        //void drawModels(Shader& shader);
    private:
        void cleanup();
};
