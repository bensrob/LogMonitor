CC=g++ -Wall -pthread -o $@	

DEP=include/*
OBJ=$(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))

bin/logmonitor:	$(OBJ)
		$(CC) $(OBJ)

build/%.o: 	src/%.cpp $(DEP)
		$(CC) $< -c

clean:
		@rm bin/* -f	|| true
		@rm build/* -f	|| true
		@make



