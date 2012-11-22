
CPP=g++
OPT=-g -DTMPDEBUG -DSHOWPROBLEM -I/opt/local/include/libxml2 -I./parser/include
#OPT=-g -DTMPDEBUG -DTRACE
#OPT=-O3 -DNDEBUG
CXXFLAGS =-Wall $(OPT)
LDFLAGS=-L/opt/local/lib -lxml2 -lz -lpthread -liconv -lm
EXEC=snail

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: Solver.h parser/MyParser.h
Variable.o: Domain.h
Constraint.o: Relation.h
Problem.o: Variable.h Constraint.h
Solver.o: Problem.h VariableOrderingHeuristic.h Propagator.h
VariableOrderingHeuristic.o: Variable.h
Propagator.o: Problem.h

%.o: %.c
	$(CPP) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
