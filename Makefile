MAKEFLAGS+=-j4
CXXFLAGS+=-O0 -Wall -Wextra -pedantic -pthread -g	
CC=g++ -o $@	
DEP=include/*
OBJ=$(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))

bin/logmonitor:	$(OBJ)
		$(CC) $(CXXFLAGS) $(OBJ)

build/%.o: 	src/%.cpp $(DEP)
		$(CC) $(CXXFLAGS) -include include/stl.h $< -c

stl:
		g++ $(CXXFLAGS) include/stl.h

clean:
		sudo rm bin/logfile -f	 || true
		sudo rm build/*.o   -f	 || true
		sudo rm build/config/* -f|| true
		bash -c "./scripts/defaults.sh"
		@+make

