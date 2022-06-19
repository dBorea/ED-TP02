#include <fstream>
#include <cstring>
#include <getopt.h>
#include "List.hpp"
#include "RankedString.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

void parseArgs(int argc, char *argv[], char inputName[], char outputName[], char logName[], bool &regMem, bool &optReg){
	extern char *optarg;
	logName[0] = 0;
	inputName[0] = 0;
	outputName[0] = 0;

	for(int opt; (opt=getopt(argc, argv, "i:I:o:O:p:l")) != EOF;){
		switch(opt){
			case 'i':
			case 'I':
				strcpy(inputName, optarg);
				break;

			case 'o':
			case 'O':
				strcpy(outputName, optarg);
				break;

			case 'p':
				strcpy(logName, optarg);
				erroAssert(strlen(logName)>0, "Com a opção -p, o nome do arquivo de registro deve ser informado.");
				optReg = true;
				break;
				
			case 'l':
				regMem = true;
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

void processaTexto(std::ifstream& inputFile, List& listaDePalavras, bool afterOrder=0, CustomAlphaCmp* ordemCustomizada = nullptr){
	std::string tempString;
	for(int i=0; inputFile >> tempString; i++){
		if(tempString == "#ORDEM") return;
		
		for(int j=tempString.size()-1; j>=0; j--){
			if(tempString[j] <= 'Z' && tempString[j] >= 'A'){
				tempString[j] += 32;
			}
			if(ispunct(tempString[j]) && tempString[j] != '-')
				tempString.erase(j, 1);
		}

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

void parseInput(std::ifstream& inputFile, std::ofstream& outputFile){

	List listaDePalavras;
	CustomAlphaCmp* ordemCustomizada;

	std::string tempString;
	std::string inputOrder("");

	inputFile >> tempString;
	erroAssert(tempString == "#ORDEM" || tempString == "#TEXTO", "Erro de index: #TEXTO ou #ORDEM não encontrados no início da entrada");

	if(tempString == "#ORDEM") { 
		processaOrdem(inputFile, inputOrder);
		ordemCustomizada = new CustomAlphaCmp(inputOrder);
		processaTexto(inputFile, listaDePalavras, 1, ordemCustomizada);
	}
	else { 
		processaTexto(inputFile, listaDePalavras);
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

	parseArgs(argc, argv, inputName, outputName, logName, regMem, optReg);

	std::string arqEntrada(inputName), arqSaida(outputName);
	std::ifstream inputFile(arqEntrada); erroAssert(!inputFile.fail(), "Arquivo de entrada não pôde ser aberto");
	std::ofstream outputFile(arqSaida);

	if(optReg)
		iniciaMemLog(logName);
	if(regMem)
		ativaMemLog();
	else
		desativaMemLog();

	parseInput(inputFile, outputFile);

	return (optReg)? finalizaMemLog() : 0;
}