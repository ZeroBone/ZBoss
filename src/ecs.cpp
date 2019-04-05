#include <zboss/ecs.hpp>

namespace zboss {

    void ECSEntity::addGroup(group_id_t group) {

        groupBitset[group] = true;

        manager.AddToGroup(this, group);

    }

}