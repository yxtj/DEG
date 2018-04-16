set(HEADERS
	Option.h
	load.h
)
set(SOURCES
	main.cpp
	Option.cpp
	load.cpp
)
add_executable(MotifFormatter
	${HEADERS} ${SOURCES})
target_link_libraries(MotifFormatter
	common
	io
	util
	${Boost_LIBRARIES}
)
