#pragma once
#include <complex>
#include "Equipment.h"

class Bus;

enum TYPEOFBRANCHELEMENT{ LI, CF, CS, DJ, RL, SL, RT, TR };

class Branch : public Equipment
{
public:
	Branch();
	Branch(const Branch &other);
	~Branch();
	Branch& operator=(const Branch &other);
	int code;
	float loadArea, R, X, Inom, Iadm;
	std::complex<float> I[3];
	TYPEOFBRANCHELEMENT lineElement;
	Bus *pbus1;
	Bus *pbus2;
	bool operator==(const Branch &other);
	bool operator!=(const Branch &other);
	void setBus1(Bus *bus);
	void setBus1(int busCode);
	void setBus2(Bus *bus);
	void setBus2(int busCode);
	void setTypeElement(std::string);
};