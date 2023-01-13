cmake_minimum_required (VERSION 3.1)
project (Particles)
cmake_policy(VERSION 3.3)
set(CMAKE_CXX_STANDARD 14)

# Set bin and lib directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

################################################################
# Build libpart first
################################################################
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

################################################################
# Check for FFTW lib
################################################################
option(USE_FFTW "Search for FFTW3 library and link the final executable" ON)
if(USE_FFTW)
message(STATUS "Searching for FFTW3 library. If something goes wrong, try specifying the CMake variable FFTW_USER_PATH.")

# Check where to look first
if(FFTW_USER_PATH)
set(FFTW_PATH ${FFTW_USER_PATH})
else(FFTW_USER_PATH)
set(FFTW_PATH /usr/local)
endif(FFTW_USER_PATH)

# Look for the library (includes and .so/.a)
# headers
find_file(FFTW_H fftw3.h ${FFTW_PATH}/include)
get_filename_component(FFTW_INCLUDES ${FFTW_H} DIRECTORY)
if(FFTW_INCLUDES)
    message(STATUS "fftw3.h found in ${FFTW_INCLUDES}")
endif(FFTW_INCLUDES)
include_directories(${FFTW_INCLUDES})
# library
find_library(FFTW_LIB libfftw3.a ${FFTW_PATH}/lib)
if(FFTW_LIB)
    message(STATUS "Library found in ${FFTW_LIB}")
endif(FFTW_LIB)

# Add executable and link it
add_executable(particles ${PROJECT_SOURCE_DIR}/src/main.cc)
target_link_libraries(particles part ${FFTW_LIB})

else(USE_FFTW)
message(FATAL_ERROR "Particles code does not work without FFTW library")
endif(USE_FFTW)

################################################################
# Google test
################################################################

include(GoogleTest)
enable_testing()
find_package(GTest)
if (GTEST_FOUND)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_kepler ${PROJECT_SOURCE_DIR}/src/test_kepler.cc)
add_executable(test_fft ${PROJECT_SOURCE_DIR}/src/test_fft.cc)
add_executable(test_heat ${PROJECT_SOURCE_DIR}/src/test_heat.cc)
target_link_libraries(test_kepler part ${GTEST_BOTH_LIBRARIES} ${FFTW_LIB} pthread)
target_link_libraries(test_fft part ${GTEST_BOTH_LIBRARIES} ${FFTW_LIB} pthread)
target_link_libraries(test_heat part ${GTEST_BOTH_LIBRARIES} ${FFTW_LIB} pthread)
gtest_discover_tests(test_kepler)
gtest_discover_tests(test_fft)
gtest_discover_tests(test_heat)
endif()

################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

# to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
)
add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)
