file(GLOB_RECURSE SOURCE "${ROOT_DIR}/src/*.cpp" "${ROOT_DIR}/src/*.hpp")

add_library(glbase ${SOURCE})

# find_package(glfw3 CONFIG REQUIRED)
# find_package(glad CONFIG REQUIRED)
# find_package(glm CONFIG REQUIRED)
# find_package(imgui CONFIG REQUIRED)
# find_package(Stb REQUIRED)

target_precompile_headers(glbase PRIVATE glbpch.hpp)

# target_link_libraries(${PROJECT_NAME} PUBLIC
#   glfw
#   glad::glad
#   glm::glm
#   imgui::imgui
# )

find_library(GLFW_LIBRARY glfw3 HINTS deps/libs)
find_library(GLAD_LIBRARY glad HINTS deps/libs)
find_library(IMGUI_LIBRARY imgui HINTS deps/libs)

target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW_LIBRARY})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLAD_LIBRARY})
target_link_libraries(${PROJECT_NAME} PUBLIC ${IMGUI_LIBRARY})

target_include_directories(glbase PUBLIC
  $<BUILD_INTERFACE:${ROOT_DIR}/src>
  # ${Stb_INCLUDE_DIR}
  deps/include
)