cmake_minimum_required(VERSION 3.27)
project(wonsz)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
)
file(GLOB sourcecode
  ${PROJECT_SOURCE_DIR}/include/*.h
  ${PROJECT_SOURCE_DIR}/src/*.c
)

add_executable(${PROJECT_NAME} ${sourcecode})

# file(COPY "./assets" DESTINATION "./")

# findsdl2 git submodule
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/findsdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image) 