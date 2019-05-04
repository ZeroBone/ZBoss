#ifndef ZBOSS_TILEMAP_COMPONENT_HPP
#define ZBOSS_TILEMAP_COMPONENT_HPP

#include <zboss/entity/component.hpp>
#include <zboss/assets/loaders/tilemap.hpp>

namespace zboss {

    class TileMapComponent : public EntityComponent {

        public:

        TileMapComponent() = default;

        explicit TileMapComponent(const std::string& tileMapName) {
            setTileMap(tileMapName);
        }

        void setTileMap(const std::string& tileMapName);

        void init() override;

        void draw() override;

        private:

        std::shared_ptr<TileMapAsset> tileMap;

    };

}

#endif //ZBOSS_TILEMAP_COMPONENT_HPP