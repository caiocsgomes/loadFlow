#include "stdafx.h"
#include "NetworkImporter.h"
#include "Circuit.h"

int main()
{	
	NetworkImporter *pImporter = new NetworkImporter();
	Circuit* pCirc;
	pCirc = pImporter->NetworkFromTxt("4BarsGrid.txt");
	return 0;
}

