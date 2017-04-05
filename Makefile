CC=g++ -Wall -pthread -o $@
INC=include/
BUI=build/
DEP=$(INC)main.h $(INC)ctail.h $(INC)threads.h $(INC)monitor.h
OBJ=$(BUI)main.o $(BUI)ctail.o $(BUI)threads.o $(BUI)monitor.o

logmonitor:	$(OBJ)
		$(CC) $(OBJ)

build/%.o: 	%.cpp $(DEP)
		$(CC) -c $<





