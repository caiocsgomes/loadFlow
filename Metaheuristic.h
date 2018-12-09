#pragma once
#include <vector>

class Bus;
struct Solution {
	Bus	  *pBus;
	int	  numberOfCapacitors;
	float gain;
};
class Metaheuristic
{
public:
	Metaheuristic();
	~Metaheuristic();
protected:
	std::vector<Solution*> vectorOfSolutions;
	float objectiveFunction(float lightLoadHours, float mediumLoadHours, float havyLoadHours);
	std::vector<Solution*> & quicksort(std::vector<Solution*> & solutions);
	int quicksortPartition(std::vector<Solution*> &solutions, int left, int right);
};

