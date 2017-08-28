add_executable(idx-map idx-map.cpp)
target_link_libraries(idx-map common io teg util
	${Boost_SYSTEM_LIBRARY}
	${Boost_PROGRAM_OPTIONS_LIBRARY})

add_executable(tmotif-count tmotif-count.cpp)
target_link_libraries(tmotif-count common io teg util
	${Boost_SYSTEM_LIBRARY}
	${Boost_PROGRAM_OPTIONS_LIBRARY})



