#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>

struct Camera {
    float fieldOfView = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};
};

struct OrbitCamera {
    glm::vec3 target{0.0f};
    float distance = 5.0f;
    float yaw = 0.0f;
    float pitch = 45.0f;
    float minDistance = 0.25f;
    float maxDistance = 1000.0f;
    float orbitSensitivity = 0.25f;
    float panSensitivity = 0.002f;
    float zoomSensitivity = 0.12f;
    bool isOrbiting = false;
    bool isPanning = false;
};

// Labels the currently active camera
struct ActiveCamera {
};

#endif