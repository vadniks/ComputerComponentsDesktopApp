cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_COMPILER "/usr/bin/clang")

project(ccad C)
set(CMAKE_C_STANDARD 11)

add_compile_options("-O3")
add_link_options("-s")

add_executable(ccad src/main.c)

file(GLOB sources CONFIGURE_DEPENDS "src/*.c" "src/*.h")
add_executable(sdl2048 ${sources})

# file hierarchy from root
# cmake-build-debug
# src
#   main.c
#   ...
# libs
#   async
#     include
#       async
#         async.h
#         ...
#   curl
#     bin
#       libcurl.so
#       ...
#     include
#       curl
#         curl.h
#         ...
#   lvgl
#     bin
#       liblvgl.a
#     include
#       lvgl
#         lvgl.h
#         src
#           lv_conf.h // #define LV_CONF_INCLUDE_SIMPLE // inside lv_conf_internal.h in src
#           lv_conf_internal.h
#           core
#           ...

# https://curl.se/libcurl/
include_directories(libs/curl/include)
file(GLOB curl_binaries CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/libs/curl/bin/*")
target_link_libraries(${PROJECT_NAME} ${curl_binaries})

# https://lvgl.io/
include_directories(libs/lvgl/include)
file(GLOB lvgl_binaries CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/libs/lvgl/bin/*")
target_link_libraries(${PROJECT_NAME} ${lvgl_binaries})

# https://github.com/naasking/async.h
include_directories(libs/async/include)
