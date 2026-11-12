#include <iostream>
#include <glm/glm.hpp>

#include "engine/ecs_core/entity_manager.hpp"
#include "engine/ecs_core/component_manager.hpp"
#include "engine/components/transform.hpp"


void testBasicECS() {
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 sca = glm::vec3(1.0f, 1.0f, 1.0f);

    std::unique_ptr<EntityManager> entity = std::make_unique<EntityManager>();
    std::unique_ptr<ComponentManager> component = std::make_unique<ComponentManager>();
    std::unique_ptr<Transform> obj = std::make_unique<Transform>();
    *obj = component->AddComponent<Transform>(entity->CreateEntity(), pos.x, pos.y, pos.z,
                                                                      rot.x, rot.y, rot.z,
                                                                      sca.x, sca.y, sca.z);
    std::cout << "Testing Basic ECS...\n";
    if(obj == nullptr) {
        std::cerr << "TEST[1] FAILED: Failed to add component\n";
    }
    else {
        std::cout << "PASSED[1]\n";
    }

    pos = glm::vec3(-5.0f, 0.0f, 0.0f);
    rot = glm::vec3(0.0f, 60.0f, 0.0f);
    sca = glm::vec3(3.0f, 3.0f, 3.0f);
    component->AddComponent<Transform>(entity->CreateEntity(), pos.x, pos.y, pos.z,
                                                               rot.x, rot.y, rot.z,
                                                               sca.x, sca.y, sca.z);

    pos = glm::vec3(5.0f, 3.0f, 10.0f);
    rot = glm::vec3(0.0f, 60.0f, 0.0f);
    sca = glm::vec3(3.0f, 3.0f, 3.0f);
    component->AddComponent<Transform>(entity->CreateEntity(), pos.x, pos.y, pos.z,
                                                               rot.x, rot.y, rot.z,
                                                               sca.x, sca.y, sca.z);
    
    for(int i = 0; i < 3; ++i) {
        *obj = component->GetComponent<Transform>(i);
        if(obj == nullptr) {
            std::cerr << "TEST[2] FAILED: Failed to fetch component\n";
        }
    }

    std::cout << "PASSED[2]\n";

    if(!component->HasComponent<Transform>(0)) {
        std::cerr << "TEST[3] FAILED: Fails to check if a component already exists in storage\n";
    }
    else {
        std::cout << "PASSED[3]\n";
    }

    std::vector<Entity> allEntities = std::move(component->GetEntitiesWith<Transform>());
    
    if(allEntities.size() != 3) {
        std::cerr << "TEST[4] FAILED: Failed to fetch all entities\n";
    }
    else{
        std::cout << "PASSED[4]\n";
    } 

}

int main() {
    testBasicECS();
    return 0;
}