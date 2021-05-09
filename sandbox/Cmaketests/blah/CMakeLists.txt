add_library(blah STATIC Blah.cpp) # Create Library executable? named blah #
target_include_directories(blah PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # Add files from the dir to the library #