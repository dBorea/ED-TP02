CXX = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
TEMP = ../temp
REGMEM = $(TEMP)/regmem
REGPERF = $(TEMP)/regperf

OBJS = $(OBJ)/textDataSorter.o $(OBJ)/memlog.o $(OBJ)/List.o $(OBJ)/ListNode.o $(OBJ)/RankedString.o
HDRS = $(INC)/msgassert.hpp $(INC)/memlog.hpp $(INC)/RankedString.hpp $(INC)/ListNode.hpp $(INC)/List.hpp

SANITIZE = -fsanitize=undefined,address -static-libasan
LDFLAGS =  -pg -O3
CXXFLAGS = -Wall -c -I$(INC) $(LDFLAGS) 

CMP = make -C ../temp compare -s
ANALISAMEM = ../analisamem/bin/analisamem
EXE = $(BIN)/tp2.exe

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

$(OBJ)/textDataSorter.o: $(HDRS) $(SRC)/textDataSorter.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/textDataSorter.o $(SRC)/textDataSorter.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

$(OBJ)/List.o: $(HDRS) $(SRC)/List.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/List.o $(SRC)/List.cpp

$(OBJ)/ListNode.o: $(HDRS) $(SRC)/ListNode.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/ListNode.o $(SRC)/ListNode.cpp

$(OBJ)/RankedString.o: $(HDRS) $(SRC)/RankedString.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/RankedString.o $(SRC)/RankedString.cpp

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
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 5 -m 10
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-5-10-gprof.txt
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 50 -m 25
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-50-25-gprof.txt
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 50 -m 5
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-50-3-gprof.txt
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 5 -m 5
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-5-5-gprof.txt
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 50 -m 50
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-50-50-gprof.txt
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 5 -m 1
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-5-1-gprof.txt
	$(EXE) -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -n 10000 -s 200 -m 50
	gprof $(EXE) gmon.out > $(REGPERF)/loremIpsum-200-50-gprof.txt

mem: $(EXE)
	rm -f $(REGMEM)/dataSorterOrder.out dataSorterText.out
	$(EXE) -p $(REGMEM)/dataSorterOrder.out -l -i $(TEMP)/entrada.txt -o $(TEMP)/saida.txt
	$(ANALISAMEM) -i $(REGMEM)/dataSorterOrder.out -p $(REGMEM)/textDataSorter-order
	$(EXE) -p $(REGMEM)/dataSorterText.out -l -i $(TEMP)/entrada_inverted.txt -o $(TEMP)/saida.txt
	$(ANALISAMEM) -i $(REGMEM)/dataSorterText.out -p $(REGMEM)/textDataSorter-text
	gnuplot $(REGMEM)/*.gp

perf: perftext perforder

perftext:$(EXE)
	$(EXE) -p $(REGPERF)/TextSort01k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 1000
	$(EXE) -p $(REGPERF)/TextSort05k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 5000
	$(EXE) -p $(REGPERF)/TextSort10k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 10000
	$(EXE) -p $(REGPERF)/TextSort15k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 15000
	$(EXE) -p $(REGPERF)/TextSort20k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 20000
	$(EXE) -p $(REGPERF)/TextSort25k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 25000
	$(EXE) -p $(REGPERF)/TextSort30k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 30000
	$(EXE) -p $(REGPERF)/TextSort35k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 35000
	$(EXE) -p $(REGPERF)/TextSort40k.out -i $(TEMP)/words_alpha_text_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 40000

perforder:$(EXE)
	$(EXE) -p $(REGPERF)/OrderedList01kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 1000
	$(EXE) -p $(REGPERF)/OrderedList05kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 5000
	$(EXE) -p $(REGPERF)/OrderedList10kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 10000
	$(EXE) -p $(REGPERF)/OrderedList15kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 15000
	$(EXE) -p $(REGPERF)/OrderedList20kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 20000
	$(EXE) -p $(REGPERF)/OrderedList25kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 25000
	$(EXE) -p $(REGPERF)/OrderedList30kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 30000
	$(EXE) -p $(REGPERF)/OrderedList35kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 35000
	$(EXE) -p $(REGPERF)/OrderedList40kText.out -i $(TEMP)/words_alpha_order_first.txt -o $(TEMP)/saida.txt -m 3 -s 5 -n 40000

clean:
	rm -f $(EXE) $(OBJS) gmon.out
