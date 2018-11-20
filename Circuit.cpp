#include "stdafx.h"
#include "Circuit.h"

Circuit::Circuit() {};

Circuit::~Circuit() {};

Bus* Circuit::getBusById(int id) {
	if (this->busVector[id - 1]) return this->busVector[id - 1];
	return nullptr;
}