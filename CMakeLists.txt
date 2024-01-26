cmake_minimum_required(VERSION 3.20)

# set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 20)
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

project(glbase)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(GLBASE_BUILD_TESTS "Build glbase engine tests" ON)

add_subdirectory(src)
if(GLBASE_BUILD_TESTS)
  add_subdirectory(tests)
endif()