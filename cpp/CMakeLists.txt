# XXX Take a look at what this minimum implies
cmake_minimum_required(VERSION 3.0)

option(DEBUG "Use library with debugging symbols" ON)

project(CryptoPalsBreaker CXX)
add_subdirectory(src)
