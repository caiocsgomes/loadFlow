#include "stdafx.h"
#include <string>
#include <map>
#include <ostream>
#include "Bus.h"

std::map<std::string, TYPEOFLOAD> mapTypeOfLoad{
	{ "0", RES },
	{ "1", COM },
	{ "2", IND },
	{ "3", SP },
	{ "4", HOS }
};

std::map<std::string, TYPEOFSHUNTELEMENT> mapTypeOfShuntElement{
	{ " ", LO },
	{ "", LO },
	{ "GR", GR },
	{ "CP", CP },
	{ "RE", RE }
};

Bus::Bus():
	code(-1), I(0), loadArea(0), loadType(RES), name(""), numberOfClients(0),
	S(0), shuntType(LO), V(0){};

Bus::~Bus() {};

Bus::Bus(Bus &other) {
	this->code = -other.code;
	this->I = other.I;
	this->loadArea = other.loadArea;
	this->loadType = other.loadType;
	this->P[0] = other.P[0];
	this->P[1] = other.P[1];
	this->P[2] = other.P[2];
	this->Q[0] = other.Q[0];
	this->Q[1] = other.Q[1];
	this->Q[2] = other.Q[2];
	this->S = other.S;
	this->shuntType = other.shuntType;
	this->stateType = other.stateType;
}

Bus& Bus::operator=(const Bus &other) {
	if (this == &other) return *this;
	this->I = other.I;
	this->loadArea = other.loadArea;
	this->loadType = other.loadType;
	this->P[0] = other.P[0];
	this->P[1] = other.P[1];
	this->P[2] = other.P[2];
	this->Q[0] = other.Q[0];
	this->Q[1] = other.Q[1];
	this->Q[2] = other.Q[2];
	this->S = other.S;
	this->shuntType = other.shuntType;
	this->stateType = other.stateType;
	return *this;
};

bool Bus::operator==(const Bus &other) const {
	return (code == other.code);
};

//Useful for debug
std::ostream &operator<<(std::ostream &out, const Bus &bus) {
	out << bus.P[0];
	out << bus.P[1];
	out << bus.P[2];
	out << bus.Q[0];
	out << bus.Q[1];
	out << bus.Q[2];
	out << bus.S;
	return out;
};

TYPEOFSHUNTELEMENT Bus::TypeOfShuntElement(std::string input) {
	return mapTypeOfShuntElement[input];
}

TYPEOFLOAD Bus::TypeOfLoad(std::string input) {
	return mapTypeOfLoad[input];
};






