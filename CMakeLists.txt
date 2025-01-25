cmake_minimum_required(VERSION 3.24)

project(
    agh_municipal_transport
    VERSION 0.99
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.xz
  URL_MD5 d55d43218e81ca3d0fc14436b7665bf1
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  EXCLUDE_FROM_ALL
)
set(BOOST_INCLUDE_LIBRARIES serialization)
set(BOOST_ENABLE_CMAKE ON)

message("Downloading Boost sources, please wait...")
FetchContent_MakeAvailable(Boost)

include_directories( inc )

file ( GLOB SOURCES "./src/*.cpp" )

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries(${PROJECT_NAME} Boost::serialization)