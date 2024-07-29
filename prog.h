#ifndef PROG_H_INCLUDED
#define PROG_H_INCLUDED
#include <fstream>
#include <iostream>
#include "f_SL.h"
#include "employer.h"
#include "worker.h"
#include "field.h"
#include "headHunter.h"
using namespace std;
#pragma once
void input(fstream& f, headHunter* hh);
void init(headHunter* p);
void outputWorkers(headHunter* hh);
void outputEmployers(headHunter* hh);
void outputEmpVac(headHunter* hh, int ans);
void outputWorkVac(headHunter* hh, int ans);
void completeVacancy(fstream& protocol, fstream& out, headHunter* hh);
void addWorker(headHunter* hh, fstream& f);
void addEmployer(headHunter* hh, fstream& f);
#endif // PROG_H_INCLUDED