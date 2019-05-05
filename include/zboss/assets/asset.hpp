#ifndef ZBOSS_ASSET_HPP
#define ZBOSS_ASSET_HPP

#include <functional>
#include <memory>
#include <string>

namespace zboss {

    class AssetLoader;

    class AssetDescriptor {

        public:

        explicit AssetDescriptor(const std::string& assetname, bool binary = true);

        virtual size_t computeHash() const;

        virtual bool compare(const AssetDescriptor& other) const;

        const std::string& name() const;

        std::string extension() const;

        bool binary() const;

        private:

        std::string assetname;

        bool _binary;

    };

    class BaseAsset {

        public:

        BaseAsset(std::shared_ptr<AssetLoader> loader, std::shared_ptr<AssetDescriptor> assetdesc);

        std::shared_ptr<AssetLoader> loader();

        std::shared_ptr<AssetDescriptor> descriptor();

        bool loaded() const;

        protected:

        void setLoaded();

        private:

        std::shared_ptr<AssetLoader> _loader;

        std::shared_ptr<AssetDescriptor> desc;

        bool isLoaded;

    };

    template <class T>
    class Asset : public BaseAsset {

        using BaseAsset::BaseAsset;

        public:

        void setAsset(T asset) {
            theAsset = asset;
            setLoaded();
        }

        T& asset() {
            return theAsset;
        }

        private:

        T theAsset;

    };

}

#endif //ZBOSS_ASSET_HPP