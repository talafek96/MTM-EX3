cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)

# include(CTest)
# enable_testing()
set(CMAKE_C_FLAGS "-std=c++11 -Wall -pedantic-errors -Werror -g -DNDEBUG")
# add_library(IntMatrix IntMatrix.cpp Auxiliaries.cpp)
add_executable(PartA partA_tester.cpp IntMatrix.cpp Auxiliaries.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)