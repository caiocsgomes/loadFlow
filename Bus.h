#pragma once
#include <string>
#include "Equipment.h"

//LO: Load, GR: Generator, CP: Capacitor, RE:Reactor 
enum TYPEOFSHUNTELEMENT { LO, GR, CP, RE };

//RE: Residential, COM: Comercial, IND: Industry, SP: Public Service, HOS: Hospital
enum TYPEOFLOAD { RES, COM, IND, SP, HOS };

class Bus : public Equipment
{
public:
	Bus();
	~Bus();
	Bus(Bus &other);
	//Aparent Power: S, Active Power: P, Reactive Power: Q, Voltage: V, Current: I, superfice available on the bus for the load flow: loadArea
	float				S, V, I, loadArea;
	float				P[3] = { 0 };
	float				Q[3] = { 0 };
	int					code, numberOfClients;
	std::string			name;
	TYPEOFSHUNTELEMENT	shuntType;
	TYPEOFSHUNTELEMENT	TypeOfShuntElement(std::string);
	TYPEOFLOAD			loadType;
	TYPEOFLOAD			TypeOfLoad(std::string);	
	Bus& operator=(const Bus &other);
	Bus* operator+(const Bus &bus);
	bool operator==(const Bus &other) const;
};




