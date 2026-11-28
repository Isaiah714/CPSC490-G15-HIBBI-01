#pragma once

#include <SDL3/SDL.h>

#include "engine/ecs_core/component_manager.hpp"

class OrbitCameraSystem {
public:
    void ProcessEvent(ComponentManager& components, const SDL_Event& event) const;
    void Update(ComponentManager& components, int viewportWidth, int viewportHeight) const;
};
