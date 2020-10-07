cmake_minimum_required(VERSION 3.17)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

llvm_map_components_to_libnames(llvm_libs support core irreader interpreter)

add_executable(Compiler ${SRC_LIST})
target_link_libraries(Compiler ${llvm_libs})