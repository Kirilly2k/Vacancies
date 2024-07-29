#include <fstream>
#include <iostream>
#include "f_SL.h"
#include "empVac.h"
#include "workVac.h"
#include "field.h"
#include "headHunter.h"
#include "prog.h"

using namespace std;

void init(education* p) {
	p->next = NULL;
}

void init(field* p) {
	p->next = NULL;
}

void init(vacancy* p) {
	p->next = NULL;
}

void init(worker* p) {
	p->edu = NULL;
	p->fld = NULL;
	p->next = NULL;
}

void init(employer* p) {
	p->fld = NULL;
	p->next = NULL;
}

void init(headHunter* p) {
	p->eduHead = NULL;
	p->eHead = NULL;
	p->fHead = NULL;
	p->vHead = NULL;
	p->wHead = NULL;
	p->evHead = NULL;
	p->wvHead = NULL;
}

void init(workVac* wv, worker* w, vacancy* v) {
	wv->vac = v;
	wv->work = w;
	wv->next = NULL;
}

void init(empVac* ev, employer* e, vacancy* v) {
	ev->vac = v;
	ev->emp = e;
	ev->edu = NULL;
	ev->next = NULL;
}

void input(fstream& f, headHunter* hh) {
	fstream workers("workers.txt", ios::in);
	fstream employers("employers.txt", ios::in);
	fstream edu("edu.txt", ios::in);
	education* eduCur = new education;
	empVac* evCur = hh->evHead;
	workVac* wvCur = hh->wvHead;
	edu >> noskipws;
	int eduLevel = 0, cnt = 0;
	char s = ' ';
	strlength temp;
	f << "Образование, отсортированное по возрастанию престижности:\n";
	while (!edu.eof()) {
		if (hh->eduHead == NULL) {
			init(eduCur);
			hh->eduHead = eduCur;
		}
		else {
			eduCur->next = new education;
			eduCur = eduCur->next;
			init(eduCur);
		}
		inputSL(edu, eduCur->name);
		outputSL(f, eduCur->name);
		f << endl;
		eduCur->level = eduLevel++;
	}
	employers >> noskipws;
	employer* empCur = new employer;
	f << "Предлагаемые вакансии:\n";
	while (!employers.eof()) {
		if (hh->eHead == NULL) {
			init(empCur);
			hh->eHead = empCur;
		}
		else {
			empCur->next = new employer;
			empCur = empCur->next;
			init(empCur);
		}
		inputSL(employers, empCur->name, true);
		inputSL(employers, temp, true);
		field* tempfld = hh->fHead;
		while (tempfld != NULL) {
			if (isEqual(tempfld->name, temp))
				break;
			tempfld = tempfld->next;
		}
		if (tempfld == NULL) {
			if (hh->fHead == NULL) {
				tempfld = new field;
				init(tempfld);
				tempfld->name = temp;
				hh->fHead = tempfld;
			}
			else {
				tempfld = hh->fHead;
				while (tempfld->next != NULL) tempfld = tempfld->next;
				tempfld->next = new field;
				tempfld = tempfld->next;
				init(tempfld);
				tempfld->name = temp;
			}
		}
		empCur->fld = tempfld;
		inputSL(employers, empCur->address, true);
		inputSL(employers, empCur->phone, true);
		inputSL(employers, temp, true);
		vacancy* tempVac = hh->vHead;
		while (tempVac != NULL) {
			if (isEqual(tempVac->name, temp))
				break;
			tempVac = tempVac->next;
		}
		if (tempVac == NULL) {
			if (hh->vHead == NULL) {
				tempVac = new vacancy;
				init(tempVac);
				tempVac->name = temp;
				hh->vHead = tempVac;
			}
			else {
				tempVac = hh->vHead;
				while (tempVac->next != NULL) tempVac = tempVac->next;
				tempVac->next = new vacancy;
				tempVac = tempVac->next;
				init(tempVac);
				tempVac->name = temp;
			}
		}
		if (evCur == NULL) {
			evCur = new empVac;
			hh->evHead = evCur;
		}
		else {
			evCur->next = new empVac;
			evCur = evCur->next;
		}
		init(evCur, empCur, tempVac);
		inputSL(employers, evCur->shedule, true);
		employers >> evCur->salary >> s;
		inputSL(employers, temp, true);
		eduCur = hh->eduHead;
		while (eduCur != NULL) {
			if (isEqual(eduCur->name, temp))
				break;
			eduCur = eduCur->next;
		}
		evCur->edu = eduCur;
		employers >> evCur->xp >> s;
		outputSL(f, evCur->emp->name);
		outputSL(f, evCur->emp->address);
		outputSL(f, evCur->emp->phone);
		outputSL(f, evCur->shedule);
		outputSL(f, evCur->edu->name);
		f << evCur->salary << " Опыт(лет): " << evCur->xp << endl;
	}
	workers >> noskipws;
	worker* workCur = new worker;
	f << "Ищут работу:\n";
	while (!workers.eof()) {
		if (hh->wHead == NULL) {
			init(workCur);
			hh->wHead = workCur;
		}
		else {
			workCur->next = new worker;
			workCur = workCur->next;
			init(workCur);
		}
		inputSL(workers, workCur->surname, true);
		inputSL(workers, workCur->name, true);
		inputSL(workers, workCur->otch, true);
		outputSL(f, workCur->surname);
		outputSL(f, workCur->name);
		outputSL(f, workCur->otch);
		f << "на специальность ";
		workers >> cnt >> s;
		for (int i = 0; i < cnt; i++) {
			inputSL(workers, temp, true);
			vacancy* tempVac = hh->vHead;
			while (tempVac != NULL) {
				if (isEqual(tempVac->name, temp))
					break;
				tempVac = tempVac->next;
			}
			if (tempVac == NULL) {
				if (hh->vHead == NULL) {
					tempVac = new vacancy;
					init(tempVac);
					tempVac->name = temp;
					hh->vHead = tempVac;
				}
				else {
					tempVac = hh->vHead;
					while (tempVac->next != NULL) tempVac = tempVac->next;
					tempVac->next = new vacancy;
					tempVac = tempVac->next;
					init(tempVac);
					tempVac->name = temp;
				}
			}
			if (wvCur == NULL) {
				wvCur = new workVac;
				hh->wvHead = wvCur;
			}
			else {
				wvCur->next = new workVac;
				wvCur = wvCur->next;
			}
			init(wvCur, workCur, tempVac);
			outputSL(f, wvCur->vac->name);
		}
		inputSL(workers, temp, true);
		field* tempfld = hh->fHead;
		while (tempfld != NULL) {
			if (isEqual(tempfld->name, temp))
				break;
			tempfld = tempfld->next;
		}
		if (tempfld == NULL) {
			if (hh->fHead == NULL) {
				tempfld = new field;
				init(tempfld);
				tempfld->name = temp;
				hh->fHead = tempfld;
			}
			else {
				tempfld = hh->fHead;
				while (tempfld->next != NULL) tempfld = tempfld->next;
				tempfld->next = new field;
				tempfld = tempfld->next;
				init(tempfld);
				tempfld->name = temp;
			}
		}
		workCur->fld = tempfld;
		workers >> workCur->xp >> s >> workCur->salary >> s;
		f << "с опытом " << workCur->xp << "и зарплатой " << workCur->salary;
		inputSL(workers, temp, true);
		eduCur = hh->eduHead;
		while (eduCur != NULL) {
			if (isEqual(eduCur->name, temp)) break;
			eduCur = eduCur->next;
		}
		f << " образование ";
		workCur->edu = eduCur;
		outputSL(f, workCur->edu->name);
		f << endl;
	}
	workers.close();
	employers.close();
	edu.close();
}

void addWorker(headHunter* hh, fstream& f) {
	int cnt = 0;
	strlength temp;
	worker* workCur = hh->wHead;
	if (hh->wHead == NULL) {
		init(workCur);
		hh->wHead = workCur;
	}
	else {
		while (workCur->next != NULL) workCur = workCur->next;
		workCur->next = new worker;
		workCur = workCur->next;
		init(workCur);
	}
	cout << "Введите фамилию работника: ";
	inputSL(workCur->surname);
	cout << "Введите имя работника: ";
	inputSL(workCur->name);
	cout << "Введите отчество работника: ";
	inputSL(workCur->otch);
	f << "Новый соискатель ";
	outputSL(f, workCur->surname);
	outputSL(f, workCur->name);
	outputSL(f, workCur->otch);
	f << "на специальность ";
	cout << "Сколько специальностей рассматривает ";
	cin >> cnt;
	cout << "Введите через энтер\n";
	workVac* wvCur = hh->wvHead;
	for (int i = 0; i < cnt; i++) {
		inputSL(temp);
		vacancy* tempVac = hh->vHead;
		while (tempVac != NULL) {
			if (isEqual(tempVac->name, temp))
				break;
			tempVac = tempVac->next;
		}
		if (tempVac == NULL) {
			if (hh->vHead == NULL) {
				tempVac = new vacancy;
				init(tempVac);
				tempVac->name = temp;
				hh->vHead = tempVac;
			}
			else {
				tempVac = hh->vHead;
				while (tempVac->next != NULL) tempVac = tempVac->next;
				tempVac->next = new vacancy;
				tempVac = tempVac->next;
				init(tempVac);
				tempVac->name = temp;
			}
		}
		if (wvCur == NULL) {
			wvCur = new workVac;
			hh->wvHead = wvCur;
		}
		else {
			wvCur->next = new workVac;
			wvCur = wvCur->next;
		}
		init(wvCur, workCur, tempVac);
		outputSL(f, wvCur->vac->name);
	}
	cout << "Введите сферу деятельности ";
	inputSL(temp);
	field* tempfld = hh->fHead;
	while (tempfld != NULL) {
		if (isEqual(tempfld->name, temp))
			break;
		tempfld = tempfld->next;
	}
	if (tempfld == NULL) {
		if (hh->fHead == NULL) {
			tempfld = new field;
			init(tempfld);
			tempfld->name = temp;
			hh->fHead = tempfld;
		}
		else {
			tempfld = hh->fHead;
			while (tempfld->next != NULL) tempfld = tempfld->next;
			tempfld->next = new field;
			tempfld = tempfld->next;
			init(tempfld);
			tempfld->name = temp;
		}
	}
	workCur->fld = tempfld;
	cout << "Опыт работы ";
	cin >> workCur->xp;
	cout << "Заработная плата ";
	cin >> workCur->salary;
	f << "с опытом " << workCur->xp << "и зарплатой " << workCur->salary;
	cout << "Образование ";
	inputSL(temp);
	education* eduCur = hh->eduHead;
	while (eduCur != NULL) {
		if (isEqual(eduCur->name, temp)) break;
		eduCur = eduCur->next;
	}
	f << " образование ";
	workCur->edu = eduCur;
	outputSL(f, workCur->edu->name);
	f << endl;
}

void addEmployer(headHunter* hh, fstream& f) {
	strlength temp;
	employer* empCur = hh->eHead;
	if (hh->eHead == NULL) {
		init(empCur);
		hh->eHead = empCur;
	}
	else {
		while (empCur->next != NULL) empCur = empCur->next;
		empCur->next = new employer;
		empCur = empCur->next;
		init(empCur);
	}
	cout << "Название компании ";
	inputSL(empCur->name);
	cout << "Сфера деятельности";
	inputSL(temp);
	field* tempfld = hh->fHead;
	while (tempfld != NULL) {
		if (isEqual(tempfld->name, temp))
			break;
		tempfld = tempfld->next;
	}
	if (tempfld == NULL) {
		if (hh->fHead == NULL) {
			tempfld = new field;
			init(tempfld);
			tempfld->name = temp;
			hh->fHead = tempfld;
		}
		else {
			tempfld = hh->fHead;
			while (tempfld->next != NULL) tempfld = tempfld->next;
			tempfld->next = new field;
			tempfld = tempfld->next;
			init(tempfld);
			tempfld->name = temp;
		}
	}
	empCur->fld = tempfld;
	cout << "Адрес ";
	inputSL(empCur->address);
	cout << "Телефон ";
	inputSL(empCur->phone);
	cout << "Какая вакансия требуется ";
	inputSL(temp);
	vacancy* tempVac = hh->vHead;
	while (tempVac != NULL) {
		if (isEqual(tempVac->name, temp))
			break;
		tempVac = tempVac->next;
	}
	if (tempVac == NULL) {
		if (hh->vHead == NULL) {
			tempVac = new vacancy;
			init(tempVac);
			tempVac->name = temp;
			hh->vHead = tempVac;
		}
		else {
			tempVac = hh->vHead;
			while (tempVac->next != NULL) tempVac = tempVac->next;
			tempVac->next = new vacancy;
			tempVac = tempVac->next;
			init(tempVac);
			tempVac->name = temp;
		}
	}
	empVac* evCur = hh->evHead;
	if (evCur == NULL) {
		evCur = new empVac;
		hh->evHead = evCur;
	}
	else {
		evCur->next = new empVac;
		evCur = evCur->next;
	}
	init(evCur, empCur, tempVac);
	cout << "График ";
	inputSL(evCur->shedule);
	cout << "Заработная плата ";
	cin >> evCur->salary;
	cout << "Требуемое образование ";
	inputSL(temp);
	education* eduCur = hh->eduHead;
	while (eduCur != NULL) {
		if (isEqual(eduCur->name, temp))
			break;
		eduCur = eduCur->next;
	}
	evCur->edu = eduCur;
	cout << "Требуемый опыт ";
	cin >> evCur->xp;
	outputSL(f, evCur->emp->name);
	outputSL(f, evCur->emp->address);
	outputSL(f, evCur->emp->phone);
	outputSL(f, evCur->shedule);
	outputSL(f, evCur->edu->name);
	f << evCur->salary << " Опыт(лет): " << evCur->xp << endl;
}

void outputWorkers(headHunter* hh) {
	int cnt = 1;
	worker* tempWork = hh->wHead;
	while (tempWork != NULL) {
		cout << cnt++ << ". ";
		outputSL(tempWork->surname);
		outputSL(tempWork->name);
		outputSL(tempWork->otch);
		tempWork = tempWork->next;
		cout << "\n";
	}
}

void outputWorkVac(headHunter* hh, int ans) {
	worker* tempWork = hh->wHead;
	for (int i = 1; i < ans; i++)
		tempWork = tempWork->next;
	empVac* tempEv = hh->evHead;
	workVac* tempWv = hh->wvHead;
	ans = 1;
	while (tempWv != NULL) {
		if (tempWv->work == tempWork) {
			tempEv = hh->evHead;
			while (tempEv != NULL) {
				if (tempEv->vac == tempWv->vac) {
					if (tempWv->work->salary <= tempEv->salary && tempWv->work->xp >= tempEv->xp &&
						tempWv->work->edu->level >= tempEv->edu->level && tempWv->work->fld == tempEv->emp->fld) {
						cout << ans++ << ". ";
						outputSL(tempEv->emp->name);
						outputSL(tempEv->emp->address);
						outputSL(tempEv->emp->phone);
						outputSL(tempEv->shedule);
						cout << tempEv->salary << endl;
					}
				}
				tempEv = tempEv->next;
			}
		}
		tempWv = tempWv->next;
	}
}

void outputEmployers(headHunter* hh) {
	int cnt = 1;
	employer* tempEmp= hh->eHead;
	while (tempEmp != NULL) {
		cout << cnt++ << ". ";
		outputSL(tempEmp->name);
		tempEmp = tempEmp->next;
		cout << "\n";
	}
}

void outputEmpVac(headHunter* hh, int ans) {
	employer* tempEmp = hh->eHead;
	for (int i = 1; i < ans; i++)
		tempEmp = tempEmp->next;
	empVac* tempEv = hh->evHead;
	workVac* tempWv = hh->wvHead;
	ans = 1;
	while (tempEv != NULL) {
		if (tempEv->emp == tempEmp) {
			tempWv = hh->wvHead;
			while (tempWv != NULL) {
				if (tempWv->vac == tempEv->vac) {
					if (tempWv->work->salary <= tempEv->salary && tempWv->work->xp >= tempEv->xp &&
						tempWv->work->edu->level >= tempEv->edu->level && tempWv->work->fld == tempEv->emp->fld) {
						cout << ans++ << ". ";
						outputSL(tempWv->work->surname);
						outputSL(tempWv->work->name);
						outputSL(tempWv->work->otch);
						cout << tempWv->work->xp << " " << tempWv->work->salary << endl;
					}
				}
				tempWv = tempWv->next;
			}
		}
		tempEv = tempEv->next;
	}
}

void completeVacancy(fstream& protocol, fstream& out, headHunter* hh) {
	empVac* tempEv = hh->evHead;
	workVac* tempWv = hh->wvHead;
	bool stop = true;
	protocol << "\nНачало распределения заявок\n";
	out << "\nНачало распределения заявок\n";
	cout << "\nНачало распределения заявок\n";
	while (tempWv != NULL && hh->evHead != NULL) {
		tempEv = hh->evHead;
		stop = true;
		while (tempEv != NULL) {
			if (tempEv->vac == tempWv->vac) {
				if (tempWv->work->salary <= tempEv->salary && tempWv->work->xp >= tempEv->xp &&
					tempWv->work->edu->level >= tempEv->edu->level && tempWv->work->fld == tempEv->emp->fld) {
					outputSL(protocol, tempWv->work->surname);
					outputSL(protocol, tempWv->work->name);
					outputSL(protocol, tempWv->work->otch);
					outputSL(out, tempWv->work->surname);
					outputSL(out, tempWv->work->name);
					outputSL(out, tempWv->work->otch);
					outputSL(tempWv->work->surname);
					outputSL(tempWv->work->name);
					outputSL(tempWv->work->otch);
					cout << "заключил договор с ";
					out << "заключил договор с ";
					protocol << "заключил договор с ";
					outputSL(protocol, tempEv->emp->name);
					outputSL(out, tempEv->emp->name);
					outputSL(tempEv->emp->name);
					cout << "на должность ";
					out << "на должность ";
					protocol << "на должность ";
					outputSL(protocol, tempEv->vac->name);
					outputSL(out, tempEv->vac->name);
					outputSL(tempEv->vac->name);
					cout << "с окладом ";
					out << "с окладом ";
					protocol << "с окладом ";
					cout << tempEv->salary << endl;
					out << tempEv->salary << endl;
					protocol << tempEv->salary << endl;
					if (tempEv == hh->evHead) {
						tempEv = tempEv->next;
						hh->evHead = tempEv;
						stop = false;
					}
					else {
						empVac* curEv = hh->evHead;
						while (curEv->next != tempEv) curEv = curEv->next;
						curEv->next = tempEv->next;
					}
					if (tempWv == hh->wvHead) {
						tempWv = tempWv->next;
						hh->wvHead = tempWv;
						stop = false;
					}
					else {
						workVac* curWv = hh->wvHead;
						while (curWv->next != tempWv) curWv = curWv->next;
						curWv->next = tempWv->next;
					}
					break;
				}
			}
			tempEv = tempEv->next;
		}
		if(stop) tempWv = tempWv->next;
	}
}