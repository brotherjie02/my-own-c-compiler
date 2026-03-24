cmake_minimum_required(VERSION 3.23)

project(MyOwnCCompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(MyOwnCCompiler ${SOURCES})

target_include_directories(MyOwnCCompiler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(MSVC)
    target_compile_options(MyOwnCCompiler PRIVATE /W4)
else()
    target_compile_options(MyOwnCCompiler PRIVATE -Wall -Wextra -pedantic)
endif()