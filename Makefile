CC=g++ -Wall -pthread
INC=include/
BUI=build/
DEP=$(INC)main.h $(INC)ctail.h $(INC)threads.h $(INC)monitor.h
OBJ=$(BUI)main.o $(BUI)ctail.o $(BUI)threads.o $(BUI)monitor.o

logmonitor:	$(OBJ)
		$(CC) $(OBJ) -o bin/$@

build/%.o: 	src/%.cpp $(DEP)
		$(CC) -c $< -o $@

clean:
		rm bin/logmonitor -f
		rm build/*.o -f
		make logmonitor



