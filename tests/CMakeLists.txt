find_package(Qt6 REQUIRED COMPONENTS Test)

set(SVG_EDITOR_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/ShapeDataTests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FileManagerTests.cpp)

set_property(GLOBAL APPEND PROPERTY SVG_EDITOR_SOURCE_FILES ${SVG_EDITOR_TEST_SOURCES})

add_executable(shape_data_tests ShapeDataTests.cpp)
target_include_directories(shape_data_tests PRIVATE ${CMAKE_SOURCE_DIR}/SVG_Editor)
target_link_libraries(shape_data_tests PRIVATE svg_editor_core Qt6::Test svg_editor_warnings)

add_executable(file_manager_tests FileManagerTests.cpp)
target_include_directories(file_manager_tests PRIVATE ${CMAKE_SOURCE_DIR}/SVG_Editor)
target_link_libraries(file_manager_tests PRIVATE svg_editor_core Qt6::Test svg_editor_warnings)

add_custom_target(svg_editor_tests DEPENDS shape_data_tests file_manager_tests)

add_test(NAME shape_data_tests COMMAND shape_data_tests)
add_test(NAME file_manager_tests COMMAND file_manager_tests)
