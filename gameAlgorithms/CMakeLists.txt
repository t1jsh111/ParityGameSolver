set(SOURCE_FILES
        src/ProgressMeasuresAlgo.cpp
        )

set(HEADER_FILES
        inc/ProgressMeasuresAlgo.h
        )

add_library(GameAlgorithmsLibrary ${SOURCE_FILES})
target_include_directories(GameAlgorithmsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(GameAlgorithmsLibrary PUBLIC ${CMAKE_SOURCE_DIR}/parsing/inc)