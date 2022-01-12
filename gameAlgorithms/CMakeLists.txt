set(SOURCE_FILES
        src/ProgressMeasuresAlgo.cpp
        src/Ordering.cpp
        src/OtherWorkingListOrderer.cpp
        src/ImprovedWorkingListOrderer.cpp
        src/WorkingListOrderer.cpp)

set(HEADER_FILES
        inc/Ordering.h
        inc/ProgressMeasuresAlgo.h
        inc/OtherWorkingListOrderer.h
        inc/ImprovedWorkingListOrderer.h
        inc/WorkingListOrderer.h
        inc/Orderer.h
        )

add_library(GameAlgorithmsLibrary ${SOURCE_FILES})
target_include_directories(GameAlgorithmsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(GameAlgorithmsLibrary PUBLIC ${CMAKE_SOURCE_DIR}/parsing/inc)