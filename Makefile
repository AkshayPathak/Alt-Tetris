CXX = g++-5
CXXFLAGS = -std=c++14
OBJECTS = Block.o  Cell.o  Game.o  GraphicsDisplay.o  Grid.o  Interpreter.o  Level0.o  Level1.o  Level2.o  Level3.o  Level4.o  Level.o  main.o  Observer.o  Score.o  Subject.o  TextDisplay.o  window.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	-rm *.o quadris
