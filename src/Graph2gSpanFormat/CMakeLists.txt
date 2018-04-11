set(HEADERS
	Option.h
)
set(SOURCES
	main.cpp
	Option.cpp
)
add_executable(Graph2gSpanFormat
	${HEADERS} ${SOURCES})
target_link_libraries(Graph2gSpanFormat
	common
	io
	util
	${Boost_LIBRARIES}
)
