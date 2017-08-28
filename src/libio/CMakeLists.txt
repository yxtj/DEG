set(HEADERS
	io.h
)
set(SOURCES
	io.cpp
)
add_library(io
	${HEADERS} ${SOURCES})
target_link_libraries(io common
	${Boost_FILESYSTEM_LIBRARY}
)