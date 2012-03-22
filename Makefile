
CPP=g++
OPT=-g -DTMPDEBUG
#OPT=-O3 -DNDEBUG
CXXFLAGS =-Wall $(OPT)

LDFLAGS=
EXEC=snail

all: $(EXEC)

$(EXEC): main.o Domain.o Variable.o Relation.o Constraint.o Problem.o
	$(CPP) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: Variable.h Constraint.h
Variable.o: Domain.h
Constraint.o: Relation.h
Problem.o: Variable.h Constraint.h

%.o: %.c
	$(CPP) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
