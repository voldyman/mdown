
include_directories(${THIRD_PARTY_DIR})

# libzmq
option(ZMQ_BUILD_TESTS OFF)
option(WITH_PERF_TOOL OFF)
add_subdirectory(${THIRD_PARTY_DIR}/libzmq)
include_directories("${THIRD_PARTY_DIR}/libzmq/include")

# cppzmp
file(GLOB CPPZMQ_HEADERS "${THIRD_PARTY_DIR}/cppzmq/*.hpp")
add_library(cppzmq INTERFACE)
target_sources(cppzmq INTERFACE ${CPPZMQ_HEADERS})
add_dependencies(cppzmq libzmq-static)

# gflags
add_subdirectory("${THIRD_PARTY_DIR}/gflags")
#include_directories("${THIRD_PARTY_DIR}/gflags/src")

# cereal
include_directories("${THIRD_PARTY_DIR}/cereal/include")
