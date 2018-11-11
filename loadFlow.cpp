#include "stdafx.h"
#include "NetworkImporter.h"
#include "Circuit.h"
#include "Flow.h"

int main()
{	
	NetworkImporter *pImporter = new NetworkImporter();
	Circuit* pCirc;
	pCirc = pImporter->NetworkFromTxt("4BarsGrid.txt");
	delete pImporter;
	Flow* pFlow = new Flow(pCirc, std::complex<float> (1.05f, 0.0f), 0.001);
	pFlow->execute();
	delete pFlow;
	return 0;
}

