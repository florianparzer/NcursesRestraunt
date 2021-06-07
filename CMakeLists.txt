cmake_minimum_required(VERSION 3.10.0)
project(reservation C CXX)
set(CMAKE_BUILD_TYPE "Debug")

enable_testing()
find_package(Threads REQUIRED)
include(${CMAKE_CURRENT_SOURCE_DIR}/modules/GTest_ExternalProject.cmake)
include(GoogleTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/modules/CodeCoverage.cmake)
append_coverage_compiler_flags()

include_directories(include)

file(GLOB_RECURSE SRC_FILES *.c CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})


add_library(${PROJECT_NAME}_lib SHARED ${SRC_FILES})

#add test source files
file(GLOB_RECURSE TEST_FILES tests/*.cxx CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME}_unit_tests ${TEST_FILES})

add_dependencies(${PROJECT_NAME}_unit_tests
    ${PROJECT_NAME}_lib
    libgtest
    libgtest_main
)

target_link_libraries(${PROJECT_NAME}_unit_tests
    ${PROJECT_NAME}_lib
    libgtest
    libgtest_main
)

gtest_discover_tests(${PROJECT_NAME}_unit_tests)
setup_target_for_coverage_gcovr_html(
    NAME ${PROJECT_NAME}_coverage
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}
    DEPENDENCIES ${PROJECT_NAME}_unit_tests
    EXCLUDE "${CMAKE_CURRENT_BINARY_DIR}/gtest/*" "tests/*"
)







