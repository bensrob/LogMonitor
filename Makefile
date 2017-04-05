CC=g++ -Wall -pthread
DEP=include/*
OBJ=$(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))

logmonitor:	$(OBJ)
		$(CC) $(OBJ) -o bin/$@

build/%.o: 	src/%.cpp $(DEP)
		$(CC) -c $< -o $@

clean:
		@rm bin/* -f	|| true
		@rm build/* -f	|| true
		make logmonitor



