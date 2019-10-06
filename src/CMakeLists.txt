add_library(celestiale celestiale.cpp)
target_include_directories(celestiale PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Setting this to the library only avoids errors in 3rd party dependencies which are compile with e.g. -Werror
target_compile_options(celestiale PUBLIC -Wall -pedantic)
# Include code-coverage settings:
target_link_libraries(celestiale PUBLIC coverage_config)
