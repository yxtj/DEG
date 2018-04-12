set(HEADERS
	Option.h
	dump.h
)
set(SOURCES
	main.cpp
	Option.cpp
	dump.cpp
)
add_executable(GraphFormater
	${HEADERS} ${SOURCES})
target_link_libraries(GraphFormater
	common
	io
	util
	${Boost_LIBRARIES}
)
