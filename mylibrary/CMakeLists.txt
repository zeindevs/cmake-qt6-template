cmake_minimum_required(VERSION 3.16)

project(mylibrary)

# static library or add (mylibrary SHARED ... for shared library
add_library(mylibrary
  src/mylibrary.cpp)

target_include_directories(mylibrary PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include)