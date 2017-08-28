set(HEADERS
	Edge.h
	Graph.h
	Motif.h
	MotifBuilder.h
	Subject.h
	SubjectInfo.h
)
set(SOURCES
	Edge.cpp
	Graph.cpp
	Motif.cpp
	MotifBuilder.cpp
	SubjectInfo.cpp
)
add_library(common
	${HEADERS} ${SOURCES})
