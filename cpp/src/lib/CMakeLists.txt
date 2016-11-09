include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

set(files
    data.cpp
)
add_library(CryptoBreaker SHARED ${files})

add_definitions(-std=c++11 -g -O0)
