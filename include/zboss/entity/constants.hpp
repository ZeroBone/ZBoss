#ifndef ZBOSS_ENTITY_CONSTANTS_HPP
#define ZBOSS_ENTITY_CONSTANTS_HPP

#include <bitset>
#include <array>
#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace zboss {

    class EntityComponent;

    class EntityConstants {

        public:

        static const size_t maxComponents = 32;

        using ComponentId = std::size_t;
        using group_id_t = std::size_t;

    };

}

#endif //ZBOSS_ENTITY_CONSTANTS_HPP