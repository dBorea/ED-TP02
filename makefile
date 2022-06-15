CXX = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
TEMP = ../temp
REGMEM = $(TEMP)/regmem
REGPERF = $(TEMP)/regperf
EXECFILES = $(TEMP)/execfiles

OBJS = $(OBJ)/textDataSorter.o $(OBJ)/jogador.o $(OBJ)/mesaDePoker.o $(OBJ)/memlog.o
HDRS = $(INC)/msgassert.hpp $(INC)/cartaDeBaralho.hpp $(INC)/jogador.hpp $(INC)/mesaDePoker.hpp $(INC)/memlog.hpp

SANITIZE = #-fsanitize=undefined,address -static-libasan
CXXFLAGS = -Wall -c -I$(INC) -g $(SANITIZE) -O3
LDFLAGS = $(SANITIZE) -g -O3

EXE = $(BIN)/tp2.exe



$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

$(OBJ)/textDataSorter.o: $(HDRS) $(SRC)/textDataSorter.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/textDataSorter.o $(SRC)/textDataSorter.cpp 

$(OBJ)/jogador.o: $(HDRS) $(SRC)/jogador.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/jogador.o $(SRC)/jogador.cpp

$(OBJ)/mesaDePoker.o: $(HDRS) $(SRC)/mesaDePoker.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/mesaDePoker.o $(SRC)/mesaDePoker.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp