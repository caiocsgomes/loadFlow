#include "stdafx.h"
#include "Flow.h"
#include "Bus.h"
#include "Branch.h"


Flow::Flow(Circuit* circ, float voltage, float referenceTolerance)
	: pCirc(circ), voltageReference(voltage), tolerance(referenceTolerance), oldLosses(0), newLosses(0) {};

Flow::~Flow() {};

//This method will initialize the voltage in all buses with the reference voltage (first bus) 
void Flow::startVoltages() {
	for (Bus* pBus : this->pCirc->busVector) {
		pBus->Vr = this->voltageReference;
	}
};


void Flow::refreshLosses() {
	this->oldLosses = this->newLosses;
};

void Flow::calculateCurrentBus() {
	for (Bus* pBus : this->pCirc->busVector) {
		pBus->Ir = (pBus->P[0] * pBus->Vr + pBus->Q[0] * pBus->Vi) / (pow(pBus->Vr, 2) + pow(pBus->Vi, 2));
		pBus->Ii = (pBus->P[0] * pBus->Vi + pBus->Q[0] * pBus->Vr) / (pow(pBus->Vr, 2) + pow(pBus->Vi, 2));
	}
}

void Flow::calculateCurrentBranch() {
	for (int index = pCirc->busVector.size(); index >= 0; index--) {

	}
}




