cmake_minimum_required(VERSION 3.16)

project(SVG_Editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

option(SVG_EDITOR_ENABLE_WARNINGS "Enable strict compiler warnings." ON)
option(SVG_EDITOR_ENABLE_CLANG_TIDY "Enable clang-tidy during builds when available." ON)

if(DEFINED ENV{Qt6_DIR})
  list(APPEND CMAKE_PREFIX_PATH "$ENV{Qt6_DIR}")
endif()

if(DEFINED ENV{Qt6_ROOT})
  list(APPEND CMAKE_PREFIX_PATH "$ENV{Qt6_ROOT}")
endif()

add_subdirectory(SVG_Editor)

include(CTest)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

get_property(SVG_EDITOR_SOURCE_FILES GLOBAL PROPERTY SVG_EDITOR_SOURCE_FILES)

if(CLANG_FORMAT_EXE AND SVG_EDITOR_SOURCE_FILES)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXE} -i ${SVG_EDITOR_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting SVG Editor sources with clang-format")

  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror ${SVG_EDITOR_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Checking SVG Editor formatting with clang-format")
else()
  add_custom_target(format
    COMMAND ${CMAKE_COMMAND} -E echo "clang-format not found; install LLVM tools to enable formatting.")
  add_custom_target(format-check
    COMMAND ${CMAKE_COMMAND} -E echo "clang-format not found; install LLVM tools to enable format checks.")
endif()

if(CLANG_TIDY_EXE AND SVG_EDITOR_SOURCE_FILES)
  add_custom_target(lint
    COMMAND ${CLANG_TIDY_EXE}
            -quiet
            -p ${CMAKE_BINARY_DIR}
            --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
            ${SVG_EDITOR_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-tidy over SVG Editor sources")
else()
  add_custom_target(lint
    COMMAND ${CMAKE_COMMAND} -E echo "clang-tidy not found; install LLVM tools to enable lint checks.")
endif()

add_custom_target(typecheck DEPENDS SVG_Editor)

if(TARGET svg_editor_tests)
  add_dependencies(typecheck svg_editor_tests)
endif()
