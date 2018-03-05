include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

if (DEBUG_LIB)
    add_compile_options(-g -O0)
    set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -O0")
else (DEBUG_LIB)
    add_compile_options(-O3)
endif (DEBUG_LIB)


set(files
    Utils.cc
    ByteStream.cc
)

add_library(CryptoBreaker SHARED ${files})
