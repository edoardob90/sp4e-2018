cmake_minimum_required (VERSION 3.0)
project (Particles)
cmake_policy(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)

# Set bin and lib directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})


################################################################
# Check for FFTW lib
################################################################
message(STATUS "Searching for FFTW3 library. If something goes wrong, try specifying the CMake variable FFTW_USER_PATH.")

if(${FFTW_USE_STATIC_LIBS})
    message(STATUS "Searching for FFTW3 static libraries ONLY")
endif()

# Check where to look first
if(FFTW_USER_PATH)
    message(STATUS "Searching for FFTW3 library first in ${FFTW_USER_PATH}")
    set(FFTW_ROOT ${FFTW_USER_PATH})
else(FFTW_USER_PATH)
    message(STATUS "Searching for FFTW3 library in standard /usr/local")
    set(FFTW_ROOT /usr/local)
endif(FFTW_USER_PATH)

# Look for the library (includes and .so/.a)

find_package(FFTW REQUIRED)

# headers
#find_file(FFTW_H fftw3.h ${FFTW_PATH}/include)
#get_filename_component(FFTW_INCLUDES ${FFTW_H} DIRECTORY)
#if(FFTW_INCLUDES)
#    message(STATUS "fftw3.h found in ${FFTW_INCLUDES}")
#endif(FFTW_INCLUDES)

include_directories(${FFTW_INCLUDE_DIRS})

## library
#find_library(FFTW_LIB NAMES libfftw3.a libfftw3.so ${FFTW_PATH}/lib)
#if(FFTW_LIB)
#    message(STATUS "Library found in ${FFTW_LIB}")
#endif(FFTW_LIB)

################################################################
# Build libpart
################################################################
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Add main executable and link it to FFTW and libpart
add_executable(particles ${PROJECT_SOURCE_DIR}/src/main.cc)
target_link_libraries(particles part ${FFTW_LIBRARIES})

################################################################
# Build and link pypart
# (must be after FFTW is found)
################################################################
set(PYPART_SRC ${PROJECT_SOURCE_DIR}/src)
set(PYB11_SRC ${PROJECT_SOURCE_DIR}/src/pybind11)

#find_package(pybind11 REQUIRED)
add_subdirectory(${PYB11_SRC})

add_library(pypart MODULE ${PYPART_SRC}/pypart.cc)

target_link_libraries(pypart PRIVATE pybind11::module)
target_link_libraries(pypart PRIVATE part)
target_link_libraries(pypart PRIVATE ${FFTW_LIBRARIES})
set_target_properties(pypart PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                    SUFFIX "${PYTHON_MODULE_EXTENSION}")

file(COPY ${PROJECT_SOURCE_DIR}/src/particles.py DESTINATION ${CMAKE_BINARY_DIR})

################################################################
# Google test
################################################################
option(BUILD_GTESTS "Compile the Google tests for some feature of particles code" OFF)
if (BUILD_GTESTS)
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
    endif(GTEST_FOUND)
else (BUILD_GTESTS)
    message(STATUS "Google Test disabled by default. If you want to run tests, add BUILD_GESTS flag to CMake.")
endif(BUILD_GTESTS)

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
