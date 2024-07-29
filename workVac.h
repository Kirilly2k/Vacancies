#pragma once
#ifndef WORKVAC_H_INCLUDED
#define WORKVAC_H_INCLUDED
#include "SL.h"
#include "worker.h"
#include "vacancy.h"
struct workVac {
	worker* work;
	vacancy* vac;
	workVac* next;
};
#endif
