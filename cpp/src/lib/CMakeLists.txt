include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

#set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++14 -Wall")
add_definitions("-std=c++14 -Wall")
if (DEBUG_LIB)
    set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -O0")
else (DEBUG_LIB)
    set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -O3")
endif (DEBUG_LIB)


set(files
    Utils.cc
    Encoding.cc
)

add_library(CryptoBreaker SHARED ${files})

