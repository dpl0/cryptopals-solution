cmake_minimum_required(VERSION 3.0)

enable_testing()
project(CryptoPalsBreaker CXX)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
option(DEBUG_LIB "Use library with debugging symbols" ON)

add_custom_target(solve
    COMMAND ./solve.sh
    WORKING_DIRECTORY src/solutions)

add_subdirectory(src)
