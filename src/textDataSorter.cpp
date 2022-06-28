#include <fstream>
#include <cstring>
#include <getopt.h>
#include "List.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

void parseArgs(int argc, char *argv[], char inputName[], char outputName[], char logName[], bool &regMem, bool &optReg, int &insertionThresholdArg, int &pivotArg, int &nPalavras){
	extern char *optarg;
	logName[0] = 0;
	inputName[0] = 0;
	outputName[0] = 0;

	for(int opt; (opt=getopt(argc, argv, "i:I:o:O:m:M:s:S:p:ln:")) != EOF;){
		switch(opt){
			case 'i':
			case 'I':
				strcpy(inputName, optarg);
				break;

			case 'o':
			case 'O':
				strcpy(outputName, optarg);
				break;
			
			case 'm':
			case 'M':
				pivotArg = atoi(optarg);
				break;
			
			case 's':
			case 'S':
				insertionThresholdArg = atoi(optarg);
				break;

			case 'p':
				strcpy(logName, optarg);
				erroAssert(strlen(logName)>0, "Com a opção -p, o nome do arquivo de registro deve ser informado.");
				optReg = true;
				break;
				
			case 'l':
				regMem = true;
				break;
			
			case 'n':
				nPalavras = atoi(optarg);
				break;
		}
	}

	if(regMem)
		regMem = optReg;

	erroAssert(strlen(inputName)>0, "Arquivo de entrada não foi informado corretamente.");
	erroAssert(strlen(outputName)>0, "Arquivo de saída não foi informado corretamente.");
}

void processaOrdem(std::ifstream& inputFile, std::string& inputOrder){
	std::string tempString;
	for(int i=0; inputFile >> tempString; i++){
		if(tempString == "#TEXTO") return;
		inputOrder.append(tempString);
	}
}

void processaTexto(std::ifstream& inputFile, List& listaDePalavras, int nPalavras, bool afterOrder=0, CustomAlphaCmp* ordemCustomizada = nullptr){
	std::string tempString;
	for(int i=0; inputFile >> tempString; i++){
		if(tempString == "#ORDEM") return;
		
		if(i >= nPalavras) continue;

		for(int j=tempString.size()-1; j>=0; j--){
			if(tempString[j] <= 'Z' && tempString[j] >= 'A'){
				tempString[j] += 32;
			}
			if(ispunct(tempString[j]) && tempString[j] != '-')
				tempString.erase(j, 1);
		}

		if(tempString[tempString.size()-1] == '-') tempString.erase(tempString.size()-1, 1);

		ListNode* nodo = listaDePalavras.search(tempString);
		if(nodo!=nullptr) nodo->incrementaData();
		else{
			if(afterOrder)
				listaDePalavras.insertNewNode(RankedString(tempString, ordemCustomizada));
			else
				listaDePalavras.insertNewNode(RankedString(tempString));
		}
	}
}

void parseInput(std::ifstream& inputFile, std::ofstream& outputFile, List listaDePalavras, int nPalavras){

	CustomAlphaCmp* ordemCustomizada;

	std::string tempString;
	std::string inputOrder("");

	inputFile >> tempString;
	erroAssert(tempString == "#ORDEM" || tempString == "#TEXTO", "Erro de index: #TEXTO ou #ORDEM não encontrados no início da entrada");

	if(tempString == "#ORDEM") { 
		processaOrdem(inputFile, inputOrder);
		ordemCustomizada = new CustomAlphaCmp(inputOrder);
		processaTexto(inputFile, listaDePalavras, nPalavras, 1, ordemCustomizada);
	}
	else { 
		processaTexto(inputFile, listaDePalavras, nPalavras);
		processaOrdem(inputFile, inputOrder);
		ordemCustomizada = new CustomAlphaCmp(inputOrder);
		listaDePalavras.updateOrder(ordemCustomizada);
		listaDePalavras.sortList();
	}

	listaDePalavras.printToOutput(outputFile);
}

int main(int argc, char *argv[]){
	char logName[100], inputName[100], outputName[100];
	bool optReg = false, regMem = false;
	int pivotArg = 0, insertThresholdArg = INSERTION_THRESHOLD, nPalavras = 50000;

	parseArgs(argc, argv, inputName, outputName, logName, regMem, optReg, insertThresholdArg, pivotArg, nPalavras);
	std::string arqEntrada(inputName), arqSaida(outputName);
	std::ifstream inputFile(arqEntrada); erroAssert(!inputFile.fail(), "Arquivo de entrada não pôde ser aberto");
	std::ofstream outputFile(arqSaida);

	List listaDePalavras;
	listaDePalavras.setInsertionTreshold(insertThresholdArg);

	if(optReg)
		iniciaMemLog(logName);
	if(regMem)
		ativaMemLog();
	else
		desativaMemLog();

	parseInput(inputFile, outputFile, listaDePalavras, nPalavras);

	return (optReg)? finalizaMemLog() : 0;
}