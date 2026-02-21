cmake_minimum_required(VERSION 3.10)
project(client VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDES ${PROJECT_SOURCE_DIR}/include/*.hpp)
add_executable(client ${SOURCES} ${INCLUDES})

# Include SFML
target_include_directories(client PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../SFML/include
)

link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)
target_link_libraries(client PUBLIC sfml-network)
