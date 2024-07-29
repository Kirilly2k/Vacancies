#ifndef	EMPLOYER_H_INCLUDED
#define EMPLOYER_H_INCLUDED
#include "SL.h"
#include "field.h"
#pragma once
struct employer
{
	strlength name;
	strlength address;
	strlength phone;
	field* fld;
	employer* next;
};

#endif // EMPLOYER_H_INCLUDED
