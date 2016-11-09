set(dirs
    set1
)

# Add all the directories in the set of dirs
foreach(dir ${dirs})
    add_subdirectory(${dir})
endforeach(dir in dirs)

# target_link_libraries()
if (DEBUG)
    link_libraries(${dirs} debug CryptoBreaker )
else (DEBUG)
    link_libraries(${dirs} optimized CryptoBreaker )
endif (DEBUG)
