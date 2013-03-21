#Makefile for search :

SRC= $(wildcard *.cc)
OBJ= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cc=.o)))


all: $(OBJ)

$(OBJ_DIR)/Solver.o: $(INC_DIR)/problem/Problem.h \
                     $(INC_DIR)/heuristic/VariableOrderingHeuristic.h \
                     $(INC_DIR)/heuristic/Dom.h \
                     $(INC_DIR)/heuristic/DomOnDDeg.h \
                     $(INC_DIR)/heuristic/DomOnDeg.h \
                     $(INC_DIR)/heuristic/Lexico.h \
                     $(INC_DIR)/propagator/Propagator.h \
                     $(INC_DIR)/propagator/BinaryForwardChecking.h \
                     $(INC_DIR)/propagator/binaryAC3.h

$(OBJ_DIR)/%.o: %.cc
	$(CC) $(INC) $(CXXFLAGS) -o $@ -c $< 


