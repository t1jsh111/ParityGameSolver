set(SOURCE_FILES
        src/Parser.cpp
        src/Node.cpp
        src/ParityGame.cpp
        src/ProgressMeasure.cpp
        )

set(HEADER_FILES
        inc/Parser.h
        inc/Node.h
        inc/ParityGame.h
        inc/ProgressMeasure.h
        )

add_library(ParsingLibrary ${SOURCE_FILES})
target_include_directories(ParsingLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)