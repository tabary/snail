#Makefile for snail :

#Set up directories
export SRC_DIR = ./src
export INC_DIR = $(SRC_DIR)/include
export OBJ_DIR = ./obj
export BIN_DIR = ./bin

#Set up project
export EXEC = snail

# Define compilation flags  
export CC = ~/tools/bin/g++ 

#standard options
#export OPT =-g -DTMPDEBUG  
#debug options
export OPT=-g -DTMPDEBUG -DSHOWPROBLEM -DTRACE
#competition options
#export OPT=-O3 -DNDEBUG

export CXXFLAGS= -std=c++11 -Wall $(OPT)
export LIBS= -L$(HOME)/tools/lib -lxml2 -lz -lpthread -liconv -lm -lstdc++
INC = -I$(INC_DIR)
INC+= -I$(INC_DIR)/parser 
INC+= -I$(INC_DIR)/problem 
INC+= -I$(INC_DIR)/heuristic 
INC+= -I$(INC_DIR)/propagator
INC+= -I$(INC_DIR)/search

INC+=-I $(HOME)/tools/include/libxml2
export INC

HEADER=$(wildcard $(INC_DIR)/*.hh $(INC_DIR)/parser/*.hh $(INC_DIR)/problem/*.hh $(INC_DIR)/search/*.hh $(INC_DIR)/heuristic/*.hh $(INC_DIR)/propagator/*.hh )
SRC= $(wildcard $(SRC_DIR)/*.cc $(SRC_DIR)/problem/*.cc $(SRC_DIR)/search/*.cc $(SRC_DIR)/heuristic/*.cc $(SRC_DIR)/propagator/*.cc )

OBJ=$(addprefix obj/,$(notdir $(SRC:.cc=.o)))

all: $(OBJ)
	g++ -Wall $(OPT) -o $(BIN_DIR)/$(EXEC) $(OBJ) $(LIBS) 

obj/%.o: src/%.cc $(HEADER)
	g++ $(CXXFLAGS) $(INC) -c $< -o $@

obj/%.o: src/parser/%.cc $(HEADER)
	g++ $(CXXFLAGS) $(DEFINES) $(INC) -c $< -o $@

obj/%.o: src/problem/%.cc $(HEADER)
	g++ $(CXXFLAGS) $(DEFINES) $(INC) -c $< -o $@

obj/%.o: src/search/%.cc $(HEADER)
	g++ $(CXXFLAGS) $(DEFINES) $(INC) -c $< -o $@

obj/%.o: src/heuristic/%.cc $(HEADER)
	g++ $(CXXFLAGS) $(DEFINES) $(INC) -c $< -o $@

obj/%.o: src/propagator/%.cc $(HEADER)
	g++ $(CXXFLAGS) $(DEFINES) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(EXEC_DIR)

mrproper: clean
	rm -rf $(EXEC_DIR)
	

