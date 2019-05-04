#ifndef ZBOSS_ENTITY_CONSTANTS_HPP
#define ZBOSS_ENTITY_CONSTANTS_HPP

#include <bitset>
#include <array>
#include <iostream>
#include <unordered_map>

namespace zboss {

    class EntityComponent;

    class EntityConstants {

        public:

        static const size_t maxComponents = 32;
        static const size_t maxGroups = 32;

        using ComponentId = std::size_t;
        using group_id_t = std::size_t;

        using component_bitset_t = std::bitset<maxComponents>;
        using group_bitset_t = std::bitset<maxGroups>;
        using component_array_t = std::array<EntityComponent*, maxComponents>;

    };

    inline static EntityConstants::ComponentId allocateComponentId();

    template <class T>
    inline static EntityConstants::ComponentId getComponentTypeId() noexcept;

    inline static EntityConstants::ComponentId allocateComponentId() {

        static EntityConstants::ComponentId counter = 0u;

        return counter++;

    }

    template <class T>
    inline static EntityConstants::ComponentId getComponentTypeId() noexcept {
        // for every component type the static variable is different, so the counting will be separated

        // return std::type_index(typeid(T));

        // static_assert(std::is_base_of<EntityComponent, T>::value, "");

        /*static bool inited = false;
        static EntityConstants::ComponentId typeId;

        if (!inited) {
            inited = true;
            typeId = allocateComponentId();
        }

        std::cout << typeId << std::endl;

        return typeId;*/

        static const EntityConstants::ComponentId typeId = allocateComponentId();
        // std::cout << typeId << std::endl;

        // dsize_t a = sizeof(T);

        return typeId;

    }

}

#endif //ZBOSS_ENTITY_CONSTANTS_HPP