find_path(SDL2_INCLUDE_DIR NAMES SDL.h PATH_SUFFIXES SDL2)
find_library(SDL2_LIBRARY NAMES libSDL2 SDL2)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    SDL2
    FOUND_VAR SDL2_FOUND
    REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR
)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)