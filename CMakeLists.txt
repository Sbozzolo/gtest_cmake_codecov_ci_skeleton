cmake_minimum_required (VERSION 2.8.7)
project (celestiale LANGUAGES CXX)

set( LEARN_CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( LEARN_CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

macro(require_cpp11)
        if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.0)
                # CMake 3.1 has built-in CXX standard checks.
                message("-- Setting C++11")
                set(CMAKE_CXX_STANDARD 11)
                set(CMAKE_CXX_STANDARD_REQUIRED on)
        else()
                if (CMAKE_CXX_COMPILER_ID MATCHES "GCC")
                    message ("-- GNU CXX (-std=c++11)")
                    list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
                elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
                    message ("-- CLang CXX (-std=c++11)")
                    list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
                else()
                    message ("-- celestiale requires C++11. Your compiler does not support it.")
                endif()
        endif()
endmacro()

require_cpp11()

include_directories( include )

# Move compiled binaries to bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE)
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
    )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE)

add_subdirectory(src)

option (BUILD_TESTING "Build the testing tree." OFF)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  add_subdirectory(tests)
else()
  add_executable(celestiale_main src/celestiale_main.cpp)
  target_link_libraries(celestiale_main PRIVATE celestiale)
endif()
