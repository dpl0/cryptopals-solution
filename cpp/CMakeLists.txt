# XXX Take a look at what this minimum means
cmake_minimum_required(VERSION 3.0)

enable_testing()
project(CryptoPalsBreaker CXX)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
option(DEBUG_LIB "Use library with debugging symbols" ON)

add_subdirectory(src)
