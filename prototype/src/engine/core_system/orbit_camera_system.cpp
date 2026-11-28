#include "engine/core_system/orbit_camera_system.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include <glm/gtc/matrix_transform.hpp>

#include "engine/components/camera.hpp"
#include "engine/components/transform.hpp"

/**
 * @brief Poll and process SDL input events to rotate, pan, and zoom the orbtal camera
 */
void OrbitCameraSystem::ProcessEvent(ComponentManager& components, const SDL_Event& event) const {
    const std::vector<Entity>& camera = components.GetEntitiesWith<Camera, ActiveCamera, OrbitCamera, Transform>();
    // If no active orbital camera exists, skip processing
    if (camera.empty())
        return;
    else {
        Entity cameraEntity = camera[0];
        OrbitCamera& orbit = components.GetComponent<OrbitCamera>(cameraEntity);

        // Poll click inputs to set whether user is currently panning or rotating the camera
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            const bool pressed = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
            
            if (event.button.button == SDL_BUTTON_LEFT) {
                orbit.isOrbiting = pressed;
            } 
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                orbit.isPanning = pressed;
            }
            return;
        }
        // Poll mouse movement to rotate or pan the camera if the corresponding mouse button is held
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            if (orbit.isOrbiting) {
                orbit.yaw += event.motion.xrel * orbit.orbitSensitivity;

                orbit.pitch = std::clamp(orbit.pitch - event.motion.yrel * orbit.orbitSensitivity, -89.0f, 89.0f);
            }

            if (orbit.isPanning) {
                const float yawRadians = glm::radians(orbit.yaw);
                const float pitchRadians = glm::radians(orbit.pitch);

                const glm::vec3 offset = glm::vec3(
                    std::cos(pitchRadians) * std::sin(yawRadians),
                    std::sin(pitchRadians),
                    std::cos(pitchRadians) * std::cos(yawRadians)
                );
                const glm::vec3 forward = -offset;
                const glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
                const glm::vec3 up = glm::normalize(glm::cross(right, forward));

                const float scale = orbit.distance * orbit.panSensitivity;
                orbit.target += (-right * event.motion.xrel + up * event.motion.yrel) * scale;
            }
            return;
        }

        // Poll mouse scroll inputs to control camera zoom
        if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            const float direction = event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1.0f : 1.0f;
            const float zoomFactor = std::pow(1.0f - orbit.zoomSensitivity, event.wheel.y * direction);
            orbit.distance = std::clamp(orbit.distance * zoomFactor, orbit.minDistance, orbit.maxDistance);
        }
    }
}

/**
 * @brief Update the camera position and matrices
 */
void OrbitCameraSystem::Update(ComponentManager& components, int viewportWidth, int viewportHeight) const {
    const std::vector<Entity>& camera = components.GetEntitiesWith<Camera, ActiveCamera, OrbitCamera, Transform>();
    // If no active orbital camera exists, skip processing
    if (camera.empty())
        return;
    else {
        Entity cameraEntity = camera[0];
        if (viewportWidth <= 0 || viewportHeight <= 0) {
            throw std::invalid_argument("OrbitCameraSystem viewport dimensions must be positive");
        }

        Camera& camera = components.GetComponent<Camera>(cameraEntity);
        OrbitCamera& orbit = components.GetComponent<OrbitCamera>(cameraEntity);
        Transform& transform = components.GetComponent<Transform>(cameraEntity);

        orbit.distance = std::clamp(orbit.distance, orbit.minDistance, orbit.maxDistance);
        orbit.pitch = std::clamp(orbit.pitch, -89.0f, 89.0f);

        const float yawRadians = glm::radians(orbit.yaw);
        const float pitchRadians = glm::radians(orbit.pitch);

        const glm::vec3 offset = glm::vec3(
            orbit.distance * std::cos(pitchRadians) * std::sin(yawRadians),
            orbit.distance * std::sin(pitchRadians),
            orbit.distance * std::cos(pitchRadians) * std::cos(yawRadians)
        );

        transform.xPos = orbit.target.x + offset.x;
        transform.yPos = orbit.target.y + offset.y;
        transform.zPos = orbit.target.z + offset.z;

        const glm::vec3 position(transform.xPos, transform.yPos, transform.zPos);
        camera.view = glm::lookAt(position, orbit.target, glm::vec3(0.0f, 1.0f, 0.0f));
        camera.projection = glm::perspective(
            glm::radians(camera.fieldOfView),
            static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight),
            camera.nearPlane,
            camera.farPlane
        );
    }
}
