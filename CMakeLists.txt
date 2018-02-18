#   CMakeLists.txt
#   CMake assembly file for hpc++11 project.

cmake_minimum_required(VERSION 3.3)
cmake_policy(SET CMP0011 NEW)
cmake_policy(SET CMP0048 NEW)

project(hpc++11
        VERSION 0.0.0
        LANGUAGES CXX)

find_package(OpenMP REQUIRED)

#   Setup compiler flags.
set(CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CXX_STANDARD} -Wall -Wextra -Wpedantic -g")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")
endif()

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

set(CMAKE_CXX_FLAGS_TSAN "-g -fsanitize=thread -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in tsan build"
    FORCE)

#   Import targets from Google Benchmark.
add_subdirectory(deps/benchmark EXCLUDE_FROM_ALL)

#   Setup include directories.
include_directories(deps/benchmark)
include_directories(include)

#   Define source groups.
set(CXX_SOURCES src/hpc++11_cxx.cc)
set(OMP_SOURCES src/hpc++11_omp.cc)

#   Build benchmark for C++ Thread Library.
add_executable(hpc++11-cxx src/main.cc ${CXX_SOURCES})
add_executable(hpc++11-cxx-bench benchmark/main.cc ${CXX_SOURCES})

target_link_libraries(hpc++11-cxx pthread)
target_link_libraries(hpc++11-cxx-bench pthread benchmark)

#   Build benchmark based on OpenMP.
add_executable(hpc++11-omp-bench benchmark/main.cc ${OMP_SOURCES})

target_link_libraries(hpc++11-omp-bench benchmark omp)
