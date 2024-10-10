cmake_minimum_required(VERSION 3.27)
project(lab2_1)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.0)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(lab2_1 main_qt.cpp
        main_sfml.cpp

)

target_link_libraries(lab2_1
        PRIVATE
        Qt6::Core
        Qt6::Widgets
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
)


add_subdirectory(Google_tests)

include_directories(
        include
)

