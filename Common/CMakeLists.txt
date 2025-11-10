cmake_minimum_required(VERSION 3.15)
project(common LANGUAGES CXX)

# Header-only library
add_library(common INTERFACE)

# Make this directory available to consumers
target_include_directories(common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# (Optional) So the header shows up in VS
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/PacketData.h)
set_target_properties(common PROPERTIES SOURCES "${HEADER_FILES}")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
