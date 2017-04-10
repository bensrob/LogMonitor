MAKEFLAGS+=-j4
CXXFLAGS+=-O0 -Wall -Wextra -pedantic -pthread -g -fno-sized-deallocation
CC=g++ -o $@ $(CXXFLAGS)
DEP=include/* pch/pch.h.gch
OBJ=$(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))
INC=-include pch/pch.h -include include/memman.h

bin/logmonitor:	$(OBJ)
		$(CC) $(OBJ)

build/%.o: 	src/%.cpp $(DEP)
		$(CC) $(INC) $< -c

pch/pch.h.gch:	pch/pch.h
		$(CC) pch/pch.h

clean:
		sudo rm bin/logfile -f	 || true
		sudo rm build/*.o   -f	 || true
		sudo rm build/config/* -f|| true
		bash -c "./scripts/defaults.sh"
		@+make

