link_libraries(glbase)

file(GLOB_RECURSE SOURCE "*.cpp" "*.hpp")

project(tests)

add_executable(${PROJECT_NAME} ${SOURCE})

# set(DATA_DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/data)

# add_custom_command(
#   TARGET ${PROJECT_NAME} POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#   ${CMAKE_SOURCE_DIR}/data ${DATA_DESTINATION}
# )

# add_custom_target(
#   copy_data_folder ALL
#   DEPENDS ${DATA_DESTINATION}
# )