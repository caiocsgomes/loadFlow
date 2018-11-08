#pragma once
#include "Circuit.h"
class Flow
{
public:
	Flow(Circuit* circ, float referenceVoltage, float referenceTolerance);
	~Flow();
	float voltageReference;	
	Circuit* pCirc;
	float oldRealLosses, newRealLosses, oldImaginaryLosses, newImaginaryLosses;
	float tolerance;
private:
	void startVoltages(void);
	void refreshLosses(void);
	void calculateCurrentBus(void);
	void calculateCurrentBranch(void);
	void calculatePowerLoss(void);
};

