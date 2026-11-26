#ifndef __COMPONENT_MANAGER__
#define __COMPONENT_MANAGER__

#include "component_storage.hpp"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <stdexcept>
#include <utility>
#include <cstdint>

using Entity = uint32_t;

class ComponentManager {
private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentPools;

    /**
     * @brief Get the storage of a specified component type or create it if it does not exist
     * @return The storage of the specified component type or the newly created storage
     */
    template<typename T>
    ComponentStorage<T>& GetOrCreateStorage() {
        std::type_index type = typeid(T);

        auto it = componentPools.find(type);

        // If there is no component storage with the specified type create one
        if (it == componentPools.end()) {
            auto storage = std::make_unique<ComponentStorage<T>>();

            auto* storage_ptr = storage.get();

            componentPools[type] = std::move(storage);
            
            return *storage_ptr;
        }

        // Otherwise return the storage found
        return *static_cast<ComponentStorage<T>*>(it->second.get());
    }

    /**
     * @brief Get the storage of a specified component type
     * @return The storage of the specified component type
     */
    template<typename T>
    ComponentStorage<T>* GetStorage() {
        std::type_index type = typeid(T);

        auto it = componentPools.find(type);

        // Return nullptr if no storage with type found
        if (it == componentPools.end()) return nullptr;

        // Otherwise return the storage found
        return static_cast<ComponentStorage<T>*>(it->second.get());
    }

public:

    /**
     * @brief Add a Component of a specified component type with the given parameters
     * @param entity The specified entity id index to store the component at
     * @param parameters The parameters of the component to store (e.g. xPos, yPos, zPos, xRot, yRot, zRot, xScale, yScale, zScale for Transform)
     * @return The inserted component data
     */
    template<typename T, typename... Params>
    T& AddComponent(Entity entity, Params&&... parameters) {
        auto& storage = GetOrCreateStorage<T>();

        // Try to add a component with the specified parameters
        //  Uses variadic templates perfect forwarding 
        auto [it, inserted] = storage.components.try_emplace(entity, std::forward<Params>(parameters)...);

        return it->second;
    }

    /**
     * @brief Get a component of a specified type from a specified entity id
     * @param entity The specified entity index to get the component from
     * @return The fetched component
     */
    template<typename T>
    T& GetComponent(Entity entity) {
        auto* storage = GetStorage<T>();

        if (!storage) throw std::runtime_error("Component storage missing!");

        return storage->components.at(entity);
    }

    /**
     * @brief Check if a given entity has a component
     * @param entity The specified entity index to check
     * @return true if the entity has a given component type, false otherwise
     */
    template<typename T>
    bool HasComponent(Entity entity) {
        auto* storage = GetStorage<T>();
        return storage && storage->components.contains(entity);
    }

    /**
     * @brief Get all entities stored with specified component types
     * @return A vector of entities with the given component
     */
    template<typename T, typename... Ts>
    std::vector<Entity> GetEntitiesWith() {
        std::vector<Entity> result;

        // Get the component storage of the first specified component type
        auto* firstStorage = GetStorage<T>();
        if (!firstStorage) return result;

        // For each entity with the first component type, check if it has all of the other component types
        for (const auto& [entity, component] : firstStorage->components) {
            if ((HasComponent<Ts>(entity) && ...))
            {
                result.push_back(entity);
            }
        }

        return result;
    }
};

#endif