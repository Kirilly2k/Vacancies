#pragma once
#ifndef EMPVAC_H_INCLUDED
#define EMPVAC_H_INCLUDED
#include "SL.h"
#include "employer.h"
#include "vacancy.h"
struct empVac {
	employer *emp;
	vacancy* vac;
	strlength shedule;
	unsigned int salary;
	unsigned int xp; //опыт
	education* edu;
	empVac* next;
};
#endif
