cmake_minimum_required(VERSION 3.10)
project(server VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDES ${PROJECT_SOURCE_DIR}/include/*.hpp)
add_executable(server ${SOURCES} ${INCLUDES})

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(server PUBLIC OpenMP::OpenMP_CXX)
endif()

# Include SFML
target_include_directories(server PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../SFML/include
)

link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)
target_link_libraries(server PUBLIC sfml-network)

