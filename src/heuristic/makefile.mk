#Makefile for heuristic :

SRC= $(wildcard *.cc)
OBJ= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cc=.o)))


all: $(OBJ)

$(OBJ_DIR)/Dom.o: $(INC_DIR)/heuristic/VariableOrderingHeuristic.h
$(OBJ_DIR)/DomOnDDeg.o: $(INC_DIR)/heuristic/VariableOrderingHeuristic.h
$(OBJ_DIR)/DomOnDeg.o: $(INC_DIR)/heuristic/VariableOrderingHeuristic.h
$(OBJ_DIR)/DomThenDDeg.o: $(INC_DIR)/heuristic/VariableOrderingHeuristic.h
$(OBJ_DIR)/VariableOrderingHeuristic.o: $(INC_DIR)/problem/Variable.h 

$(OBJ_DIR)/%.o: %.cc
	$(CC) $(INC) $(CXXFLAGS) -o $@ -c $< 


