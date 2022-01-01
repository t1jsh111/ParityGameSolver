cmake_minimum_required(VERSION 3.17)
project(ParityGameSolver)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parsing)


add_executable(ParityGameSolver main.cpp)

target_link_libraries(ParityGameSolver PUBLIC ParsingLibrary)
target_include_directories(ParityGameSolver PUBLIC parsing/inc)

file(COPY ${ParityGameSolver_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
