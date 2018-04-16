set(HEADERS
	io.h
	fs.h
)
set(SOURCES
	io.cpp
	fs.cpp
)
add_library(io
	${HEADERS} ${SOURCES})
target_link_libraries(io common
	${Boost_FILESYSTEM_LIBRARY}
)