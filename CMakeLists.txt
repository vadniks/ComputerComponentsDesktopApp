
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(ccda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wno-nullability-completeness")

add_compile_options("-O3")
add_link_options("-s")

file(GLOB sources CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.tpp" "src/*/*.cpp" "src/*/*.hpp" res/resources.qrc)
add_executable(${PROJECT_NAME} ${sources})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Concurrent)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Gui Qt::Widgets Qt6::Network Qt6::Concurrent)

# TODO: RPATH, pack()
# ldd cmake-build-debug/ccda | awk '{print $3}'
