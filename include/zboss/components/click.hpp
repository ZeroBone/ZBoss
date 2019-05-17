#ifndef ZBOSS_CLICK_COMPONENT_HPP
#define ZBOSS_CLICK_COMPONENT_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>

#include <zboss/components/transform.hpp>

namespace zboss {

    class ClickComponent : public EntityComponent {

        private:

        void (*callback)(std::shared_ptr<Entity> self, SDL_MouseButtonEvent&);

        public:

        explicit ClickComponent(void (*cb)(std::shared_ptr<Entity> self, SDL_MouseButtonEvent&)) : callback(cb) {}

        void init() override;

        bool input() override;

    };

}

#endif //ZBOSS_CLICK_HPP