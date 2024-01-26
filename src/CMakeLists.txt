file(GLOB_RECURSE SOURCE "${ROOT_DIR}/src/*.cpp" "${ROOT_DIR}/src/*.hpp")

add_library(glbase ${SOURCE})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)

target_precompile_headers(glbase PRIVATE glbpch.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
  glfw
  glad::glad
  glm::glm
  imgui::imgui
)

target_include_directories(glbase PUBLIC
  $<BUILD_INTERFACE:${ROOT_DIR}/src>
  ${Stb_INCLUDE_DIR}
  deps/include
)