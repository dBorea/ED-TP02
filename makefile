CXX = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
TEMP = ../temp
REGMEM = $(TEMP)/regmem
REGPERF = $(TEMP)/regperf

OBJS = $(OBJ)/textDataSorter.o $(OBJ)/memlog.o
HDRS = $(INC)/msgassert.hpp $(INC)/memlog.hpp $(INC)/RankedString.hpp $(INC)/ListNode.hpp $(INC)/List.hpp

SANITIZE = #-fsanitize=undefined,address -static-libasan
CXXFLAGS = -Wall -c -I$(INC) $(SANITIZE) -pg -O3
LDFLAGS = $(SANITIZE) -pg -O3

CMP = make -C ../temp compare -s
EXE = $(BIN)/tp2.exe

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

$(OBJ)/textDataSorter.o: $(HDRS) $(SRC)/textDataSorter.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/textDataSorter.o $(SRC)/textDataSorter.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

execute: $(EXE)
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
	$(CMP)

pivotTest: $(EXE)
	$(EXE) -i $(TEMP)/entradas/1.tst.i -o $(TEMP)/saidas/saida1.txt -m 5
	$(EXE) -i $(TEMP)/entradas/2.tst.i -o $(TEMP)/saidas/saida2.txt -m 5
	$(EXE) -i $(TEMP)/entradas/3.tst.i -o $(TEMP)/saidas/saida3.txt -m 5
	$(EXE) -i $(TEMP)/entradas/4.tst.i -o $(TEMP)/saidas/saida4.txt -m 5
	$(EXE) -i $(TEMP)/entradas/5.tst.i -o $(TEMP)/saidas/saida5.txt -m 5
	$(EXE) -i $(TEMP)/entradas/6.tst.i -o $(TEMP)/saidas/saida6.txt -m 5
	$(EXE) -i $(TEMP)/entradas/7.tst.i -o $(TEMP)/saidas/saida7.txt -m 5
	$(EXE) -i $(TEMP)/entradas/8.tst.i -o $(TEMP)/saidas/saida8.txt -m 5
	$(EXE) -i $(TEMP)/entradas/9.tst.i -o $(TEMP)/saidas/saida9.txt -m 5
	$(EXE) -i $(TEMP)/entradas/10.tst.i -o $(TEMP)/saidas/saida10.txt -m 5
	$(CMP)

insertionTest: $(EXE)
	$(EXE) -i $(TEMP)/entradas/1.tst.i -o $(TEMP)/saidas/saida1.txt -s 5
	$(EXE) -i $(TEMP)/entradas/2.tst.i -o $(TEMP)/saidas/saida2.txt -s 5
	$(EXE) -i $(TEMP)/entradas/3.tst.i -o $(TEMP)/saidas/saida3.txt -s 5
	$(EXE) -i $(TEMP)/entradas/4.tst.i -o $(TEMP)/saidas/saida4.txt -s 5
	$(EXE) -i $(TEMP)/entradas/5.tst.i -o $(TEMP)/saidas/saida5.txt -s 5
	$(EXE) -i $(TEMP)/entradas/6.tst.i -o $(TEMP)/saidas/saida6.txt -s 5
	$(EXE) -i $(TEMP)/entradas/7.tst.i -o $(TEMP)/saidas/saida7.txt -s 5
	$(EXE) -i $(TEMP)/entradas/8.tst.i -o $(TEMP)/saidas/saida8.txt -s 5
	$(EXE) -i $(TEMP)/entradas/9.tst.i -o $(TEMP)/saidas/saida9.txt -s 5
	$(EXE) -i $(TEMP)/entradas/10.tst.i -o $(TEMP)/saidas/saida10.txt -s 5
	$(CMP)

allParametersTest: $(EXE)
	$(EXE) -i $(TEMP)/entradas/1.tst.i -o $(TEMP)/saidas/saida1.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/2.tst.i -o $(TEMP)/saidas/saida2.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/3.tst.i -o $(TEMP)/saidas/saida3.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/4.tst.i -o $(TEMP)/saidas/saida4.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/5.tst.i -o $(TEMP)/saidas/saida5.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/6.tst.i -o $(TEMP)/saidas/saida6.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/7.tst.i -o $(TEMP)/saidas/saida7.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/8.tst.i -o $(TEMP)/saidas/saida8.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/9.tst.i -o $(TEMP)/saidas/saida9.txt -s 3 -m 6
	$(EXE) -i $(TEMP)/entradas/10.tst.i -o $(TEMP)/saidas/saida10.txt -s 3 -m 6
	$(CMP)

simpletest: $(EXE)
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt

cmp:
	$(CMP)

gprof: $(EXE)
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 5 -m 10
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-5-10-gprof.txt
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 50 -m 25
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-50-25-gprof.txt
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 50 -m 5
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-50-3-gprof.txt
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 5 -m 5
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-5-5-gprof.txt
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 50 -m 50
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-50-50-gprof.txt
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 5 -m 1
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-5-1-gprof.txt
	$(EXE) -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt -s 200 -m 50
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-200-200-gprof.txt

clean:
	rm -f $(EXE) $(OBJS) gmon.out