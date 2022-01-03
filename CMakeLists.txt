cmake_minimum_required(VERSION 3.17)
project(ParityGameSolver)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parsing)
add_subdirectory(gameAlgorithms)


add_executable(ParityGameSolver main.cpp)


target_link_libraries(ParityGameSolver PUBLIC ParsingLibrary)
target_include_directories(ParityGameSolver PUBLIC parsing/inc)

target_link_libraries(ParityGameSolver PUBLIC GameAlgorithmsLibrary)
target_include_directories(ParityGameSolver PUBLIC gameAlgorithms/inc)

file(COPY ${ParityGameSolver_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(unit_testing)