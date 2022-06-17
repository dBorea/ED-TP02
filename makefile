CXX = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
TEMP = ../temp
REGMEM = $(TEMP)/regmem
REGPERF = $(TEMP)/regperf
EXECFILES = $(TEMP)/execfiles

OBJS = $(OBJ)/textDataSorter.o $(OBJ)/memlog.o
HDRS = $(INC)/msgassert.hpp $(INC)/memlog.hpp $(INC)/RankedString.hpp $(INC)/ListNode.hpp $(INC)/List.hpp

SANITIZE = #-fsanitize=undefined,address -static-libasan
CXXFLAGS = -Wall -c -I$(INC) -g $(SANITIZE) 
LDFLAGS = $(SANITIZE) -g 

EXE = $(BIN)/tp2.exe

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

$(OBJ)/textDataSorter.o: $(HDRS) $(SRC)/textDataSorter.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/textDataSorter.o $(SRC)/textDataSorter.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

test:
	$(EXE) -i $(TEMP)/entradas/1.tst.i -o $(TEMP)/saidas/saida1.txt
	$(EXE) -i $(TEMP)/entradas/2.tst.i -o $(TEMP)/saidas/saida2.txt
	$(EXE) -i $(TEMP)/entradas/3.tst.i -o $(TEMP)/saidas/saida3.txt
	$(EXE) -i $(TEMP)/entradas/4.tst.i -o $(TEMP)/saidas/saida4.txt
	$(EXE) -i $(TEMP)/entradas/5.tst.i -o $(TEMP)/saidas/saida5.txt
	$(EXE) -i $(TEMP)/entradas/6.tst.i -o $(TEMP)/saidas/saida6.txt
	$(EXE) -i $(TEMP)/entradas/7.tst.i -o $(TEMP)/saidas/saida7.txt
	$(EXE) -i $(TEMP)/entradas/8.tst.i -o $(TEMP)/saidas/saida8.txt
	$(EXE) -i $(TEMP)/entradas/9.tst.i -o $(TEMP)/saidas/saida9.txt
	$(EXE) -i $(TEMP)/entradas/10.tst.i -o $(TEMP)/saidas/saida10.txt

simpletest:
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt

clean:
	rm -f $(EXE) $(OBJS) gmon.out