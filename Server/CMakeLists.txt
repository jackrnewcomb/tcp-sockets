# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(server VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Attempt to find OpenAL package
#find_package(OpenAL REQUIRED)

# Add the include directories for OpenAL
include_directories(${OPENAL_INCLUDE_DIR})


# Add source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDES ${PROJECT_SOURCE_DIR}/include/*.hpp)

# Add the executable
add_executable(server ${SOURCES} ${INCLUDES})

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
  target_link_libraries(server PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/../SFML/include)

link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)

# Link the executable to the libraries in the lib directory
target_link_libraries(server PUBLIC sfml-graphics)
