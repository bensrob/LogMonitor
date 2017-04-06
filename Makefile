CC=g++ -Wall -pthread -o $@	

DEP=include/*
OBJ=$(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))

bin/logmonitor:	$(OBJ)
		$(CC) $(OBJ)

build/%.o: 	src/%.cpp $(DEP)
		$(CC) $< -c

clean:
		rm bin/* -fr	|| true
		rm build/* -fr	|| true
		bash -c "./scripts/defaults.sh"
		@make



