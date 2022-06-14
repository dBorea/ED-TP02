#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
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
				strcpy(logname, optarg);
				erroAssert(strlen(logname)>0, "Com a opção -p, o nome do arquivo de registro deve ser informado.");
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

int main(){
	char logName[100], inputName[100], outputName[100];
	bool optReg = false, regMem = false;

	parseArgs(argc, argv, inputName, outputName, logName, regMem, optReg);

	if(optReg)
		iniciaMemlog(logname);
	if(regMem)
		ativaMemLog();
	else
		desativaMemLog();



	return (optReg)? finalizaMemLog() : 0;
}