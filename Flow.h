#pragma once
#include <complex>
#include "Circuit.h"
class Flow
{
public:
	Flow(Circuit* circ, std::complex<float> voltage, float referenceTolerance);
	~Flow();	
	Circuit* pCirc;
	std::complex<float> voltageReference;
	float tolerance;
	float oldLosses, newLosses, imaginaryLoss, realLoss;
	void  execute(void);
private:
	int   numberOfIterations;
	void  startVoltages(void);
	void  refreshLosses(void);
	void  calculateCurrentBus(void);
	void  calculateCurrentBranch(void);
	float calculateLossDifference(void);
	void  calculatePowerLoss(void);
	void  calculateVoltageBus(void);
};

