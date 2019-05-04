#ifndef ZBOSS_FILE_LOCATOR_HPP
#define ZBOSS_FILE_LOCATOR_HPP

#include <zboss/assets/locator.hpp>

namespace zboss {

    class FileLocator : public AssetLocator {

        public:

        explicit FileLocator(const std::string& location);

        SDL_RWops* locate(const std::string& assetname, bool binary) override;

        private:

        std::string _location;

    };

}

#endif //ZBOSS_FILE_LOCATOR_HPP