#objects = main.o Board.o Solver.o TestBoards.o
objects = main.o Board.o Solver.o

main.out: $(objects)
	g++ -o main.out $(objects)
	clear
	./main.out

#main.o: main.cc	Board.h Solver.h TestBoards.h
main.o: main.cc	Board.h Solver.h
	g++ -c main.cc

#TestBoards.o: TestBoards.cc TestBoards.h
#	g++ -c TestBoards.cc

Board.o: Board.cc Board.h
	g++ -c Board.cc

Solver.o: Solver.cc Solver.h Board.h
	g++ -c Solver.cc

clean:
	rm -f .o main
