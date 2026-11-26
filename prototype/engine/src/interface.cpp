#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include "engine/include/renderer/interface.hpp"
#include "engine/include/components/mesh.hpp"

#include <SDL3/SDL.h>

void Interface::createInterface(SDL_Window * window, SDL_GLContext * glContext) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();
}

void Interface::displayInterface(EntityManager & manager,
                                 ComponentManager & components,
                                 ModelLoader & modelLoader) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Insert")) {
        if (ImGui::MenuItem("Cube")) {
            Entity newCube = manager.CreateEntity();
            components.AddComponent<Transform>(newCube, 0.0, 0.0, 0.0, 0.0, 45.0, 0.0, 1.0, 1.0, 1.0);
            components.AddComponent<Mesh>(newCube, cubeVertexList, cubeIndexList, glm::vec3(1, 0, 0));
            modelLoader.SetupMesh(components.GetComponent<Mesh>(newCube));
        }
        ImGui::EndMenu();
    }
        
    ImGui::Separator();

    // Manipulate dropdown which lets you edit an entity
    if (ImGui::BeginMenu("Manipulate")) {
        ImGui::SliderInt("Target ID", &targetEntityID, 0, entities.size() - 1);
        // try statement incase enetity has no Transform component
        try {
            Transform& target = components.GetComponent<Transform>(entities[targetEntityID]);

            float pos[3] = {target.xPos, target.yPos, target.zPos};
            float rot[3] = {target.xRot, target.yRot, target.zRot};
            float scale[3] = {target.xScale, target.yScale, target.zScale};
            if(ImGui::DragFloat3("Position", pos, 0.01f)) {
                target.xPos = pos[0];
                target.yPos = pos[1];
                target.zPos = pos[2];
            }

            if(ImGui::DragFloat3("Rotation", rot, 0.01f)) {
                target.xRot = rot[0];
                target.yRot = rot[1];
                target.zRot = rot[2];
            }

            if(ImGui::DragFloat3("Scale", scale, 0.01f)) {
                target.xScale = scale[0];
                target.yScale = scale[1];
                target.zScale = scale[2];
            }
        }
        catch(const std::runtime_error& e) {
            ImGui::Text("%s on id: %d", e.what(), targetEntityID);
        }
        ImGui::EndMenu();
    }

	ImGui::Separator();
    ImGui::Text("%.1f FPS", io.Framerate);
    ImGui::EndMainMenuBar();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/**
 * @brief calls all ImGui functions to destroy its context and cleanup
 */
void Interface::destroyInterface() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}