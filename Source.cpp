#include <iostream>
#include <Windows.h>
#include "f_SL.h"
#include "prog.h"
#include "headHunter.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream protocol("protocol.txt", ios::out);
	fstream out("output.txt", ios::out);
	headHunter* hh = new headHunter;
	init(hh);
	input(protocol, hh);
	int todo = 1, ans = 0;
	while (todo < 6 && todo > 0) {
		cout << "������������, ������ ���� ������� �� ������� ������, ����� ����� ���������� �� ������ �����������:\n";
		cout << "1. �������� ������ ����������� ��� ������������� ������������\n";
		cout << "2. �������� ������ �������� ��� ������������� ����������\n";
		cout << "3. ������ ��������� ������\n";
		cout << "4. �������� ����������\n";
		cout << "5. �������� ������������\n";
		cout << "����� ��������� �������� ������\n";
		cin >> todo;
		switch (todo) {
		case 1:
			outputEmployers(hh);
			cin >> ans;
			outputEmpVac(hh, ans);
			break;
		case 2:
			outputWorkers(hh);
			cin >> ans;
			outputWorkVac(hh, ans);
			break;
		case 3:
			completeVacancy(protocol, out, hh);
			break;
		case 4:
			addWorker(hh, out);
			break;
		case 5:
			addEmployer(hh, out);
			break;
		}
	}
	protocol.close();
	return 0;
}