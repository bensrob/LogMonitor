MAKEFLAGS+=-j4
CXXFLAGS+=-O0 -Wall -Wextra -pedantic -pthread -g -fno-sized-deallocation -Wno-unused-variable
CC=g++ -o $@ $(CXXFLAGS)
DEP=include/* pch/pch.h.gch
PCH=pch/pch.h pch/include/*
OBJ=$(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))
INC=-include pch/pch.h

bin/logmonitor:	$(OBJ)
		$(CC) $(OBJ)

build/%.o: 	src/%.cpp $(DEP)
		$(CC) $(INC) $< -c

pch/pch.h.gch:	$(PCH)
		$(CC) pch/pch.h

fix:
		grep -rl endl | grep -v Makefile | xargs sed -i 's/std::endl/endl/g'

clean:
		sudo rm bin/logfile -f	 || true
		sudo rm build/*.o   -f	 || true
		sudo rm build/config/* -f|| true
		@+make fix
		bash -c "./scripts/defaults.sh"
		@+make

