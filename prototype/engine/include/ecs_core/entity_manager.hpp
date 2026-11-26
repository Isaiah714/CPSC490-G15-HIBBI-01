#ifndef __ENTITY_MANAGER__
#define __ENTITY_MANAGER__

#include <cstdint>
#include <vector>

using Entity = uint32_t;

class EntityManager{
private:
    Entity nextEntity = 0;
    std::vector<Entity> entities;
public:
    /**
     * @brief Creates a new entity id and stores it
     * @return The id of the newly created entity
     */
    Entity CreateEntity() {
        Entity entity = nextEntity++;
        entities.push_back(entity);
        return entity;
    }
};
#endif
