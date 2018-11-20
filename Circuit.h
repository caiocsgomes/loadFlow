#pragma once
#include <vector>
#include "Branch.h"
#include "Bus.h"
class Circuit
{
public:
	Circuit();
	~Circuit();
	Bus* getBusById(int id);
	std::vector<Branch*> branchVector;
	std::vector<Bus*> busVector;
};

