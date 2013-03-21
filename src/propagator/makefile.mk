#Makefile for propagator :

SRC= $(wildcard *.cc)
OBJ= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cc=.o)))


all: $(OBJ)

$(OBJ_DIR)/binaryAC3.o: $(INC_DIR)/propagator/Propagator.h
$(OBJ_DIR)/binaryForwardChecking.o: $(INC_DIR)/propagator/Propagator.h
$(OBJ_DIR)/Propagator.o: $(INC_DIR)/problem/Constraint.h

$(OBJ_DIR)/%.o: %.cc
	$(CC) $(INC) $(CXXFLAGS) -o $@ -c $< 


