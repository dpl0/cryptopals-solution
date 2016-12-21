function(add_test_and_libraries testname filename)
    add_executable(${testname} ${filename})
    target_link_libraries(${testname} pthread gmock gtest CryptoBreaker)
    add_test(NAME ${testname} COMMAND ${testname})
endfunction(add_test_and_libraries)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")
include_directories($ENV{GMOCK}/include
                    $ENV{GMOCK}/gtest/include)

link_directories($ENV{GMOCK}/build/googlemock
                 $ENV{GMOCK}/build/googlemock/gtest)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++14 -g -O0 -Wall")

add_test_and_libraries(UtilsTest "UtilsTest.cc")

