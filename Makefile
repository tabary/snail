
CPP=g++
OPT=-g -DTMPDEBUG
#OPT=-O3 -DNDEBUG
CXXFLAGS =-Wall $(OPT)

LDFLAGS=
EXEC=snail

all: $(EXEC)

$(EXEC): main.o Domain.o Variable.o
	$(CPP) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: Domain.h Variable.h
Variable.o: Domain.h

%.o: %.c
	$(CPP) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
