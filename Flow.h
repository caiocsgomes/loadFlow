#pragma once
#include "Circuit.h"
class Flow
{
public:
	Flow(Circuit* circ, float referenceVoltage, float referenceTolerance);
	~Flow();
	float voltageReference;	
	Circuit* pCirc;
	float oldLosses{ 0 }, newLosses{ 0 };
	float tolerance;
private:
	void startVoltages(void);
	void refreshLosses(void);
	void calculateCurrentBus(void);
	void calculateCurrentBranch(void);
};

