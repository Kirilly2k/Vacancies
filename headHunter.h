#pragma once
#ifndef HH_H_INCLUDED
#define HH_H_INCLUDED
#include "empVac.h"
#include "workVac.h"
#include "field.h"
struct headHunter {
	worker* wHead;
	employer* eHead;
	education* eduHead;
	vacancy* vHead;
	field* fHead;
	empVac* evHead;
	workVac* wvHead;
};
#endif
