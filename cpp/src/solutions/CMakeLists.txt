function(add_file_and_link_without_filetype filename termination)
    string(REGEX REPLACE ${termination} "" exe ${filename})
    add_executable(${exe} ${filename})
    if (DEBUG_LIB)
        target_link_libraries(${exe} CryptoBreaker)
    else (DEBUG_LIB)
        target_link_libraries(${exe} CryptoBreaker)
    endif (DEBUG_LIB)
endfunction(add_file_and_link_without_filetype)

# Copy file so that it can be used later
configure_file(./solve.sh ./solve.sh)

add_subdirectory(set1)
