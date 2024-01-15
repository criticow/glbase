link_libraries(glbase)

file(GLOB_RECURSE SOURCE "*.cpp" "*.hpp")

project(tests)

add_executable(${PROJECT_NAME} ${SOURCE})