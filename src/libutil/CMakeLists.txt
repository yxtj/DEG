set(HEADERS
    IndexMapper.h
    Timer.h
    Util.h
)
set(SOURCES
    IndexMapper.cpp
    Timer.cpp
    Util.cpp
)
add_library(util
    ${HEADERS} ${SOURCES})
