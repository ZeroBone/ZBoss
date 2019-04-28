#ifndef ZBOSS_LOCATOR_HPP
#define ZBOSS_LOCATOR_HPP

#include <zboss/exceptions.hpp>

#include <SDL2/SDL.h>
#include <string>

namespace zboss {

    class AssetLocatorError : public Exception {
        using Exception::Exception;
    };

    class AssetLocator {

        public:

        virtual SDL_RWops* locate(const std::string& assetname, bool binary) = 0;

    };

}

#endif //ZBOSS_LOCATOR_HPP