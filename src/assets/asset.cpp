#include <zboss/assets/asset.hpp>
#include <typeinfo>

using namespace std;

namespace zboss {

    AssetDescriptor::AssetDescriptor(const string& assetname, bool binary) : assetname(assetname), _binary(binary) {}

    size_t AssetDescriptor::computeHash() const {
        hash<string> hashfn;
        return hashfn(assetname);
    }

    bool AssetDescriptor::compare(const AssetDescriptor& other) const {
        return (assetname == other.name());
    }

    const string& AssetDescriptor::name() const {
        return assetname;
    }

    bool AssetDescriptor::binary() const {
        return _binary;
    }

    string AssetDescriptor::extension() const {
        size_t found = assetname.rfind(".");
        string result("");

        if (found != string::npos) {
            result = assetname.substr(found + 1);
        }

        return result;
    }

    BaseAsset::BaseAsset(shared_ptr<AssetLoader> loader, shared_ptr<AssetDescriptor> assetdesc)
        : _loader(loader), desc(assetdesc), isLoaded(false) {}

    shared_ptr<AssetLoader> BaseAsset::loader() {
        return _loader;
    }

    void BaseAsset::setLoaded() {
        isLoaded = true;
    }

    bool BaseAsset::loaded() const {
        return isLoaded;
    }

    shared_ptr<AssetDescriptor> BaseAsset::descriptor() {
        return desc;
    }

}