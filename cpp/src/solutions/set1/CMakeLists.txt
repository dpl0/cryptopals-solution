include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include/")

set(files
    1.cc
    2.cc
    3.cc
)

foreach(f ${files})
    add_file_and_link_without_filetype(${f} ".cc$")
endforeach(f)
