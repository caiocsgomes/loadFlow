#include "stdafx.h"
#include "stack"
#include "Metaheuristic.h"
#include "const.h"

Metaheuristic::Metaheuristic() {}

Metaheuristic::~Metaheuristic() {}

//This function will calculate the gain in dollars with the capacitor of 300kVAr installation in the bus
float Metaheuristic::objectiveFunction(float lossGainLight, float lossGainMedium, float lossGainHeavy) {
	float profit = energy::pricekWh * (lossGainLight * general::lightLoadHours + lossGainMedium * general::mediumLoadHours + lossGainHeavy * general::heavyLoadHours) - (capacitor::price300kVAr + capacitor::price300kVArInstalation);
	return profit;
}

std::vector<Solution*> &Metaheuristic::quicksort(std::vector<Solution*> &solutions) {
	int start = 0;
	int end = solutions.size() - 1;
	int partitionIndex = 0;
	std::stack<int> stack;
	stack.push(start);
	stack.push(end);

	while (stack.size() > 0) {
		end = stack.top();
		stack.pop();
		start = stack.top();
		stack.pop();

		partitionIndex = quicksortPartition(solutions, start, end);

		if (partitionIndex + 1 < end) {
			stack.push(partitionIndex + 1);
			stack.push(end);
		}

		if (start < partitionIndex - 1) {
			stack.push(start);
			stack.push(partitionIndex - 1);
		}
	}
	
	return solutions;
}

int Metaheuristic::quicksortPartition(std::vector<Solution*> &solutions, int left, int right) {
	int partitionIndex = left;
	//The number wee need to compare is the loss from the last solution
	float pivot = solutions[right]->gain;
	Solution *auxVariable;

	for (int index = left; index < right; index++) {
		//>= will sort from the biggest to the smallest
		if (solutions[index]->gain >= pivot) {
			auxVariable = solutions[partitionIndex];
			solutions[partitionIndex] = solutions[index];
			solutions[index] = auxVariable;
			partitionIndex++;
		}
	}

	auxVariable = solutions[right];
	solutions[right] = solutions[partitionIndex];
	solutions[partitionIndex] = auxVariable;
	return partitionIndex;
}

