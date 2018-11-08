#include "stdafx.h"
#include "Flow.h"
#include "Bus.h"
#include "Branch.h"


Flow::Flow(Circuit* circ, float voltage, float referenceTolerance)
	: pCirc(circ), voltageReference(voltage), tolerance(referenceTolerance), oldRealLosses(0), newRealLosses(0),
	oldImaginaryLosses(0), newImaginaryLosses(0) {};

Flow::~Flow() {};

//This method will initialize the voltage in all buses with the reference voltage (first bus) 
void Flow::startVoltages() {
	for (Bus* pBus : this->pCirc->busVector) {
		pBus->Vr = this->voltageReference;
	}
};


void Flow::refreshLosses() {
	this->oldRealLosses      = this->newRealLosses;
	this->oldImaginaryLosses = this->newImaginaryLosses;
};

void Flow::calculateCurrentBus() {
	for (Bus* pBus : this->pCirc->busVector) {
		pBus->Ir = (pBus->P[0] * pBus->Vr + pBus->Q[0] * pBus->Vi) / (pow(pBus->Vr, 2) + pow(pBus->Vi, 2));
		pBus->Ii = (pBus->P[0] * pBus->Vi + pBus->Q[0] * pBus->Vr) / (pow(pBus->Vr, 2) + pow(pBus->Vi, 2));
	}
}

void Flow::calculateCurrentBranch() {
	pCirc->branchVector[pCirc->branchVector.size() - 1]->Ir = pCirc->busVector[pCirc->busVector.size() - 1]->Ir;
	pCirc->branchVector[pCirc->branchVector.size() - 1]->Ii = pCirc->busVector[pCirc->busVector.size() - 1]->Ii;
	for (int index = pCirc->branchVector.size() - 2; index >= 0; index--) {
		pCirc->branchVector[index]->Ir = pCirc->branchVector[index + 1]->Ir + pCirc->busVector[index + 1]->Ir;
		pCirc->branchVector[index]->Ii = pCirc->branchVector[index + 1]->Ir + pCirc->busVector[index + 1]->Ii;
	}
}

void Flow::calculatePowerLoss() {
	for (Branch* pBranch : this->pCirc->branchVector) {
		this->newRealLosses      += pBranch->X * (pow(pBranch->Ir, 2));
		this->newImaginaryLosses += pBranch->X * (pow(pBranch->Ii,2));
	}
}




