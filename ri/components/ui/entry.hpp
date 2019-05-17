#ifndef ZBOSS_ENTRY_HPP
#define ZBOSS_ENTRY_HPP

#include <zboss/entity/component.hpp>
#include <zboss/entity/entity.hpp>

using namespace zboss;

class UiEntryComponent : public EntityComponent {

    public:

    void init() override;

    bool input() override;

};

#endif //ZBOSS_ENTRY_HPP