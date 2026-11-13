#ifndef __COMPONENT_STORAGE__
#define __COMPONENT_STORAGE__

#include <cstdint>
#include <unordered_map>

using Entity = uint32_t;

class IComponentStorage {
public:
    virtual ~IComponentStorage() = default;
};

template<typename Component>
class ComponentStorage : public IComponentStorage {
public:
    std::unordered_map<Entity, Component> components;
};

#endif
