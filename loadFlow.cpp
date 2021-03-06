#include "stdafx.h"
#include "NetworkImporter.h"
#include "Circuit.h"
#include "Flow.h"

int main()
{	
	NetworkImporter *pImporter = new NetworkImporter();
	Circuit* pCirc;
	pCirc = pImporter->NetworkFromTxt("84BusGrid.txt");
	Flow* pFlow = new Flow(pCirc, std::complex<float>(11.4f, 0.0f), 0.001);
	pFlow->execute();
	delete pImporter;
	delete pFlow;
	return 0;
}

