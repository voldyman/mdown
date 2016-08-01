cmake_minimum_required(VERSION 3.2)

project(mdown CXX)

set(CMAKE_CXX_STANDARD 14)

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)
include("${THIRD_PARTY_DIR}/third_party.cmake")

include_directories(src)

file(GLOB MDOWN_SOURCES src/*.cc)

add_executable(${CMAKE_PROJECT_NAME}
  ${MDOWN_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} cppzmq libzmq-static gflags)
