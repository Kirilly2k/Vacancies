#ifndef F_SL_H_INCLUDED
#define F_SL_H_INCLUDED
#include <fstream>
using namespace std;
#pragma once
void inputSL(fstream& f, struct strlength& SL);
void inputSL(fstream& f, struct strlength& SL, bool flag);
void inputSL(strlength& SL);
void outputSL(fstream& of, struct strlength SL);
void outputSL(struct strlength SL);
bool isEqual(strlength str1, strlength str2);

#endif // F_SL_H_INCLUDED
