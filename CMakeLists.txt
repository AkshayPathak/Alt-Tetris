cmake_minimum_required(VERSION 3.8)
project(Test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cc Grid.cc Grid.h Cell.cc Cell.h Block.h Block.cc Subject.cc Subject.h Observer.cc Observer.h)
add_executable(Test ${SOURCE_FILES} Grid.cc Grid.h Cell.cc Cell.h Block.h Block.cc Subject.cc Subject.h Observer.cc Observer.h)