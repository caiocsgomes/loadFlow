#include "stdafx.h"
#include <string>
#include "NetworkImporter.h"
#include "Bus.h"
#include "Branch.h"
#include "Equipment.h"
#include "Circuit.h"

Circuit* NetworkImporter::NetworkFromTxt(std::string filename) {
	std::ifstream inputFile;
	std::string line;
	Bus *pBus;
	Branch *pBranch;
	Circuit *pCirc = new Circuit();
	inputFile.open(filename);

	if (!inputFile.is_open()) return nullptr;
	
	std::getline(inputFile, line, ';');
	
	do  {
		switch (this->TypeOfElement(line)) {
			case BUS:

				//Extraction of the end of line character after reading the word
				std::getline(inputFile, line, '\n');

				
				std::getline(inputFile, line, ';');
				do  {
					pBus = new Bus();

					pBus->code = stoi(line);

					std::getline(inputFile, line, ';');
					pBus->name = line;

					std::getline(inputFile, line, ';');
					pBus->shuntType = pBus->TypeOfShuntElement(line);
					
					std::getline(inputFile, line, ';');
					pBus->loadArea = stof(line);
					
					std::getline(inputFile, line, ';');
					pBus->Pnom = stof(line);
					
					std::getline(inputFile, line, ';');
					pBus->phasesType = pBus->TypeOfPhases(line);
					
					std::getline(inputFile, line, ';');
					pBus->power[0].real(stof(line));
					
					std::getline(inputFile, line, ';');
					pBus->power[1].real(stof(line));
					
					std::getline(inputFile, line, ';');
					pBus->power[2].real(stof(line));
					
					std::getline(inputFile, line, ';');
					pBus->power[0].imag(stof(line));
					
					std::getline(inputFile, line, ';');
					pBus->power[1].imag(stof(line));
					
					std::getline(inputFile, line, ';');
					pBus->power[2].imag(stof(line));
					
					std::getline(inputFile, line, ';');
					pBus->loadType = pBus->TypeOfLoad(line);
					
					std::getline(inputFile, line, ';');
					pBus->numberOfClients = stoi(line);
					
					std::getline(inputFile, line, ';');
					pBus->stateType = pBus->TypeOfState(line);
					
					pCirc->busVector.push_back(pBus);
					
					//Extraction of the end of line character after finishing the line
					std::getline(inputFile, line, '\n');

					//Extraction of the first element to check if it is an electrical type of if
					//it is still a property of Bus
					std::getline(inputFile, line, ';');
				} while (!isKeyWord(line)); break;
			case BRANCH:

				//Extraction of the end of line character after reading the word
				std::getline(inputFile, line, '\n');

				std::getline(inputFile, line, ';');
				do {
					pBranch = new Branch();

					pBranch->setBus1(stoi(line));

					std::getline(inputFile, line, ';');
					pBranch->setTypeElement(line);
					
					std::getline(inputFile, line, ';');
					pBranch->setBus2(stoi(line));
					
					std::getline(inputFile, line, ';');
					pBranch->loadArea = stof(line);
					
					std::getline(inputFile, line, ';');
					pBranch->Z.real(stof(line));
					
					std::getline(inputFile, line, ';');
					pBranch->Z.imag(stof(line));
					
					std::getline(inputFile, line, ';');
					pBranch->Inom = stof(line);
					
					std::getline(inputFile, line, ';');
					pBranch->Iadm = stof(line);
					
					std::getline(inputFile, line, ';');
					pBranch->phasesType = pBranch->TypeOfPhases(line);

					pCirc->branchVector.push_back(pBranch);

					//Extraction of the end of line character after finishing the line
					std::getline(inputFile, line, '\n');
					
					//Extraction of the first element to check if it is an electrical type of if
					//it is still a property of Branch
					std::getline(inputFile, line, ';');
				} while (!isKeyWord(line)); break;
			default: break;
		} 
	} while (line != "FIM");

	if (pCirc) return pCirc;
	else return nullptr;
}

TYPEOFELECTRICALELEMENT NetworkImporter::TypeOfElement(std::string name) {
	if		(name == "LINHA") return BRANCH; 
	else if (name == "BARRA") return BUS;
}

bool NetworkImporter::isKeyWord(std::string keyword) {
	if ((keyword == "LINHA") || (keyword == "BARRA") || (keyword == "FIM")) return true;
	return false;
}
