#include <zboss/assets/manager.hpp>

using namespace std;

namespace zboss {

    void AssetManager::register_locator(shared_ptr<AssetLocator> locator) {
        locators.push_back(move(locator));
    }

    void AssetManager::register_loader(shared_ptr<AssetLoader> loader, const vector<string>& extensions) {
        for (const auto& ext : extensions) {
            loaders[ext] = loader;
        }
    }

    void AssetManager::unload(BaseAsset* asset) {
        auto it = cache.find(asset->descriptor());

        if (it != cache.end()) {
            cache.erase(it);
        }

        asset->loader()->unload(asset);
        delete asset;
    }

}