include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")
set(files
    data.cpp
)

# TODO Check how to use
set(cpp11 "-std=c++11")
set(debug "-g -O0")
add_definitions(${cpp11} ${debug})
add_library(CryptoBreaker SHARED ${files})
