#pragma once

#include "imgui.h"

#include "engine/include/ecs_core/entity_manager.hpp"
#include "engine/include/ecs_core/component_manager.hpp"
#include "engine/include/renderer/model_loader.hpp"

namespace Interface {
    void createInterface(SDL_Window * window, SDL_GLContext * glContext);
    void displayInterface(EntityManager    & manager,
                          ComponentManager & components,
                          ModelLoader      & modelLoader);
    void destroyInterface();
    ImGuiIO& io = ImGui::GetIO();
};