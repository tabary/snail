#Makefile for problem :



SRC= $(wildcard *.cc)
OBJ= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cc=.o)))


all: $(OBJ)

$(OBJ_DIR)/Constraint.o: $(INC_DIR)/problem/Relation.h $(INC_DIR)/problem/Variable.h
$(OBJ_DIR)/Variable.o: $(INC_DIR)/problem/Domain.h $(INC_DIR)/problem/Constraint.h
$(OBJ_DIR)/Problem.o: $(INC_DIR)/problem/Constraint.h $(INC_DIR)/problem/Variable.h


$(OBJ_DIR)/%.o: %.cc
	$(CC) $(INC) $(CXXFLAGS) -o $@ -c $< 


