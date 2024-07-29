#pragma once
#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED
#include "SL.h"
#include "education.h"
#include "field.h"
struct worker {
	strlength surname;
	strlength name;
	strlength otch;
	unsigned int xp;//опыт
	unsigned int salary;
	education* edu;
	field* fld;
	worker* next;
};
#endif