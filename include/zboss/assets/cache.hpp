#ifndef ZBOSS_CACHE_HPP
#define ZBOSS_CACHE_HPP

#include <zboss/assets/asset.hpp>

#include <unordered_map>
#include <memory>

namespace zboss {

    struct AssetHasher {
        size_t operator()(std::shared_ptr<AssetDescriptor> const& key) const {
            return key->computeHash();
        }
    };

    struct AssetPred {
        bool operator()(std::shared_ptr<AssetDescriptor> const& a, std::shared_ptr<AssetDescriptor> const& b) const {
            return a->compare(*b);
        }
    };

    class AssetCache
        : public std::unordered_map<std::shared_ptr<AssetDescriptor>, std::weak_ptr<BaseAsset>, AssetHasher, AssetPred> {
    };

}

#endif //ZBOSS_CACHE_HPP