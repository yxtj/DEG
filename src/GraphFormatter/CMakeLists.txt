set(HEADERS
	Option.h
	dump.h
)
set(SOURCES
	main.cpp
	Option.cpp
	dump.cpp
)
add_executable(GraphFormatter
	${HEADERS} ${SOURCES})
target_link_libraries(GraphFormatter
	common
	io
	util
	${Boost_LIBRARIES}
)
