#Makefile for snail :


ROOT := $(shell pwd)


#Set up directories
export SRC_DIR = $(ROOT)/src
export INC_DIR = $(ROOT)/include
export OBJ_DIR = $(ROOT)/obj
export BIN_DIR = $(ROOT)/bin

#Set up project
export EXEC = snail
export EXEC_DIR = $(BIN_DIR)/$(EXEC)

# Define compilation flags  
export CC = g++

#standard options
export OPT =-g -DTMPDEBUG    -DSHOWPROBLEM
#debug options
#export OPT=-g -DTMPDEBUG -DTRACE
#competition options
#export OPT=-O3 -DNDEBUG

export CXXFLAGS =-Wall $(OPT)
export LDFLAGS=-L/opt/local/lib -lxml2 -lz -lpthread -liconv -lm
INC = -I$(INC_DIR)
INC+= -I$(INC_DIR)/parser 
INC+= -I$(INC_DIR)/problem 
INC+= -I$(INC_DIR)/heuristic 
INC+= -I$(INC_DIR)/propagator
INC+= -I$(INC_DIR)/search

INC+= -I/opt/local/include/libxml2
export INC

MODULES = problem heuristic propagator search


all: $(EXEC_DIR)

$(EXEC_DIR): $(OBJ_DIR)/snail.o $(MODULES) 
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o $@ $(wildcard *.o $(OBJ_DIR)/*.o)

$(OBJ_DIR)/snail.o: $(INC_DIR)/search/Solver.h \
                    $(INC_DIR)/MyParser.h


$(OBJ_DIR)/snail.o: $(SRC_DIR)/snail.cc
	$(CC) $(INC) $(CXXFLAGS) -o $@ -c $<	

$(MODULES): 
	@cd $(SRC_DIR)/$@ ; \
        make  -f makefile.mk ; \
        cd $(ROOT) 
        

clean:
	rm -rf $(OBJ_DIR)/*.o

mrproper: clean
	rm -rf $(EXEC_DIR)
	

