CC=g++ -Wall -o $@ -pthread
DEP=main.h ctail.h threads.h monitor.h
OBJ=main.o ctail.o threads.o monitor.o

main: $(OBJ)
	$(CC) $(OBJ)

%.o: %.cpp $(DEP)
	$(CC) -c $<





