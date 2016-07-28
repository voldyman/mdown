cmake_minimum_required(VERSION 3.2)

project(mdown CXX)

set(CMAKE_CXX_STANDARD 14)


file(GLOB mdown_sources src/*.cc)

add_executable(${CMAKE_PROJECT_NAME}
  ${mdown_sources})
