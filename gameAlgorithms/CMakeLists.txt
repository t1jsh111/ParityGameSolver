set(SOURCE_FILES
        src/ProgressMeasuresAlgo.cpp
        src/Ordering.cpp
        src/WorkingListOrderer.cpp
        src/ImprovedWorkingListOrderer.cpp)

set(HEADER_FILES
        inc/Ordering.h
        inc/ProgressMeasuresAlgo.h
        inc/WorkingListOrderer.h
        inc/ImprovedWorkingListOrderer.h
        )

add_library(GameAlgorithmsLibrary ${SOURCE_FILES})
target_include_directories(GameAlgorithmsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(GameAlgorithmsLibrary PUBLIC ${CMAKE_SOURCE_DIR}/parsing/inc)