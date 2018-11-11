#include "stdafx.h"
#include "Flow.h"
#include "Bus.h"
#include "Branch.h"


Flow::Flow(Circuit* circ, std::complex<float> voltage, float referenceTolerance)
	: pCirc(circ), voltageReference(voltage), tolerance(referenceTolerance), oldLosses(0), newLosses(0) {};

Flow::~Flow() {};

//This method will initialize the voltage in all buses with the reference voltage (first bus) 
void Flow::startVoltages() {
	for (Bus* pBus : this->pCirc->busVector) {
		pBus->V[0] = this->voltageReference;
	}
};

void Flow::refreshLosses() {
	this->oldLosses      = this->newLosses;
};

/*Formulas to calculate Real and Imaginary parts of the current:
	Real Current      = (Real Power * Real Voltage + Imag Power * Imag Current)/((Real Voltage)^2 + (Imag Voltage)^2)
	Imaginary Current = (Real Power * Imag Voltage - Imag Power * Real Current)/((Real Voltage)^2 + (Imag Voltage)^2)
*/
void Flow::calculateCurrentBus() {
	for (int index = 1; index < this->pCirc->busVector.size(); index++) {
		pCirc->busVector[index]->I[0].real((pCirc->busVector[index]->power[0].real() * pCirc->busVector[index]->V[0].real() + pCirc->busVector[index]->power[0].imag() * pCirc->busVector[index]->V[0].imag()) / (pow(pCirc->busVector[index]->V[0].real(), 2) + pow(pCirc->busVector[index]->V[0].imag(), 2)));
		pCirc->busVector[index]->I[0].imag((pCirc->busVector[index]->power[0].real() * pCirc->busVector[index]->V[0].imag() - pCirc->busVector[index]->power[0].imag() * pCirc->busVector[index]->V[0].real()) / (pow(pCirc->busVector[index]->V[0].real(), 2) + pow(pCirc->busVector[index]->V[0].imag(), 2)));
	}
};

/*
	The current in a Branch is the current in the downstream Bus plus the current in the downstream Branch (Kirchhoff's Current Law)
*/
void Flow::calculateCurrentBranch() {
	pCirc->branchVector[pCirc->branchVector.size() - 1]->I[0].real(pCirc->busVector[pCirc->busVector.size() - 1]->I[0].real());
	pCirc->branchVector[pCirc->branchVector.size() - 1]->I[0].imag(pCirc->busVector[pCirc->busVector.size() - 1]->I[0].imag());
	for (int index = pCirc->branchVector.size() - 2; index >= 0; index--) {
		pCirc->branchVector[index]->I[0].real(pCirc->branchVector[index + 1]->I[0].real() + pCirc->busVector[index + 1]->I[0].real());
		pCirc->branchVector[index]->I[0].imag(pCirc->branchVector[index + 1]->I[0].imag() + pCirc->busVector[index + 1]->I[0].imag());
	}
};

/*
	The Power Loss in circuit is the sum of the loss in all branches of the circuit
*/
void Flow::calculatePowerLoss() {
	this->newLosses = 0;
	for (Branch* pBranch : this->pCirc->branchVector) {
		this->newLosses += (pBranch->Z.real() * (pow(pBranch->I[0].real(), 2)) + pBranch->Z.imag() * (pow(pBranch->I[0].imag(), 2)));
	}
};

float Flow::calculateLossDifference() {
	return abs(this->newLosses - this->oldLosses);
};

void Flow::calculateVoltageBus() {
	for (int index = 1; index < this->pCirc->busVector.size(); index++) {
		this->pCirc->busVector[index]->V[0] = this->pCirc->busVector[index - 1]->V[0] - this->pCirc->branchVector[index - 1]->I[0] * this->pCirc->branchVector[index - 1]->Z;
	}
};

void Flow::execute() {
	this->startVoltages();
	do {
		this->refreshLosses();
		this->calculateCurrentBus();
		this->calculateCurrentBranch();
		this->calculateVoltageBus();
		this->calculatePowerLoss();
	} while (this->calculateLossDifference() > this->tolerance);
	
}