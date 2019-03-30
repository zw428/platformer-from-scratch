project(platformer-from-scratch)

cmake_minimum_required(VERSION 3.14)

include(GNUInstallDirs)
find_package(Catch2 REQUIRED)

set(SDL_LIBS SDL2 SDL2_image SDL2_mixer SDL2_ttf)

add_subdirectory(src)
add_subdirectory(test)

add_executable(platformer-from-scratch src/main.cpp)

target_link_libraries(platformer-from-scratch
	base ${SDL_LIBS}
)

enable_testing()
