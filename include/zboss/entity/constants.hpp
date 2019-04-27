#ifndef ZBOSS_CONSTANTS_HPP
#define ZBOSS_CONSTANTS_HPP

#include <bitset>
#include <array>

namespace zboss {

    class EntityConstants {

        class EntityComponent;

        public:

        static const size_t maxComponents = 32;
        static const size_t maxGroups = 32;

        using component_id_t = size_t;
        using group_id_t = size_t;
        using component_bitset_t = std::bitset<maxComponents>;
        using group_bitset_t = std::bitset<maxGroups>;
        using component_array_t = std::array<EntityComponent*, maxComponents>;

    };

    inline EntityConstants::component_id_t allocateComponentId() {
        static EntityConstants::component_id_t counter = 0u;
        return counter++;
    }

    template <typename T>
    inline EntityConstants::component_id_t getComponentTypeId() noexcept;

    template <typename T>
    inline EntityConstants::component_id_t getComponentTypeId() noexcept {
        // for every component type the static variable is different, so the counting will be separated

        // static_assert(std::is_base_of<EntityComponent, T>::value, "");

        static EntityConstants::component_id_t typeID = allocateComponentId();
        return typeID;

    }

}

#endif //ZBOSS_CONSTANTS_HPP