set(HEADERS
	TemporalEdgeGraph.h
	TemporalEdgeMotif.h
	util-teg.h
)
set(SOURCES
	TemporalEdgeGraph.cpp
	TemporalEdgeMotif.cpp
	util-teg.cpp
)
add_library(teg
	${HEADERS} ${SOURCES})
target_link_libraries(teg common util
	${Boost_FILESYSTEM_LIBRARY}
)