
CPP=g++
OPT=-g -DTMPDEBUG
#OPT=-O3 -DNDEBUG
CXXFLAGS =-Wall $(OPT)

LDFLAGS=
EXEC=snail

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: Solver.h
Variable.o: Domain.h
Constraint.o: Relation.h
Problem.o: Variable.h Constraint.h
Solver.o: Problem.h

%.o: %.c
	$(CPP) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
