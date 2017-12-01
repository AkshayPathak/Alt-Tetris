cmake_minimum_required(VERSION 3.8)
project(Test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cc Grid.cc Grid.h Cell.cc Cell.h Block.h Block.cc Subject.cc Subject.h Observer.cc Observer.h Interpreter.cc Interpreter.h Game.cc Game.h Level.cc Level.h TextDisplay.cc TextDisplay.h Level1.cc Level1.h Level0.cc Level0.h Level2.cc Level2.h Level3.cc Level3.h Level4.cc Level4.h)
add_executable(Test ${SOURCE_FILES} Grid.cc Grid.h Cell.cc Cell.h Block.h Block.cc Subject.cc Subject.h Observer.cc Observer.h Interpreter.cc Interpreter.h Game.cc Game.h Level.cc Level.h Level1.cc Level1.h Level0.cc Level0.h Level2.cc Level2.h Level3.cc Level3.h Level4.cc Level4.h)