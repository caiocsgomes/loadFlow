#include "stdafx.h"
#include "Branch.h"
#include "Bus.h"
#include <string>
#include <map>


std::map<std::string, TYPEOFBRANCHELEMENT> mapTypeOfElement{
	{" ", LI},
	{"CF", CF},
	{"CS", CS},
	{"DJ", DJ},
	{"RL", RL},
	{"SL", SL},
	{"RT", RT},
	{"TR", TR}
};

Branch::Branch()
	:code(0), R(0), X(0), loadArea(0), Inom(0), Iadm(0), I{(0.0f, 0.0f), (0.0f, 0.0f), (0.0f, 0.0f)},
	lineElement(LI), pbus1(nullptr), pbus2(nullptr) {};

Branch::Branch(const Branch &other) {
	this->code = other.code;
	this->Iadm = other.Iadm;
	this->lineElement = other.lineElement;
	this->loadArea = other.loadArea;
	if (other.pbus1) {
		this->pbus1 = new Bus();
		this->pbus1 = other.pbus1;
	};
	if (other.pbus2) {
		this->pbus2 = new Bus();
		this->pbus2 = other.pbus2;
	};
	this->R = other.R;
};

Branch::~Branch() {
	if (this->pbus1) delete this->pbus1;
	if (this->pbus2) delete this->pbus2;
};

Branch& Branch::operator=(const Branch &other) {
	this->code = other.code;
	this->Iadm = other.Iadm;
	this->lineElement = other.lineElement;
	this->loadArea = other.loadArea;
	if (other.pbus1) {
		this->pbus1 = new Bus();
		this->pbus1 = other.pbus1;
	};
	if (other.pbus2) {
		this->pbus2 = new Bus();
		this->pbus2 = other.pbus2;
	};
	this->R = other.R;
	return *this;
};

bool Branch::operator==(const Branch &other) {
	return (this->code == other.code);
};

bool Branch::operator!=(const Branch &other) {
	return (this->code == other.code);
}
void Branch::setBus1(Bus *bus) {
	this->pbus1 = new Bus();
	this->pbus1 = bus;
};

void Branch::setBus1(int busCode) {
	this->pbus1 = new Bus();
	this->pbus1->code = busCode;
};

void Branch::setBus2(Bus *bus) {
	this->pbus2 = new Bus();
	this->pbus2 = bus;
};

void Branch::setBus2(int busCode) {
	this->pbus2 = new Bus();
	this->pbus2->code = busCode;
};
void Branch::setTypeElement(std::string type) {
	this->lineElement = mapTypeOfElement[type];
};
