cmake_minimum_required(VERSION 3.24)

project(
    agh_municipal_transport
    VERSION 0.1
    LANGUAGES CXX
)

include(FetchContent)

# Fetch Bcrypt.cpp library
FetchContent_Declare(
  Bcrypt
  GIT_REPOSITORY https://github.com/hilch/Bcrypt.cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(Bcrypt)

# Fetch yaml-cpp library
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

include_directories( inc )

file ( GLOB SOURCES "./src/*.cpp" "./src/app/*.cpp" )

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries(${PROJECT_NAME} bcrypt yaml-cpp::yaml-cpp)