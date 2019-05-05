#ifndef ZBOSS_TILEMAP_COMPONENT_HPP
#define ZBOSS_TILEMAP_COMPONENT_HPP

#include <zboss/entity/component.hpp>
#include <zboss/assets/loaders/tilemap.hpp>

namespace zboss {

    class TileMapComponent : public EntityComponent {

        public:

        TileMapComponent() = default;

        explicit TileMapComponent(const std::string& tileMapName, float scale = 1.f, uint16_t specialTiles = 0) {
            setTileMap(tileMapName);
            tileMap->asset()->setScale(scale);
            tileMap->asset()->setSpecialTiles(specialTiles);
        }

        void setTileMap(const std::string& tileMapName);

        void init() override;

        void draw() override;

        private:

        std::shared_ptr<TileMapAsset> tileMap;

    };

}

#endif //ZBOSS_TILEMAP_COMPONENT_HPP