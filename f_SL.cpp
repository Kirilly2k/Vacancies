#include "f_SL.h"
#include "SL.h"
#include <iostream>

void inputSL(fstream& f, strlength& SL, bool flag)
{
	int i = 0;
	char s;
	while (flag) {
		f >> s;
		if (s == '\n' || f.eof()) {
			flag = false;
			break;
		}
		if (s != '\n' && s != ' ') {
			SL.A[i] = s;
			i++;
		}
		if (i >= N) { while ((s != '\n') && (!f.eof())) f >> s; break; }
		if (s == ' ') break;
	}
	SL.L = i;
}

void inputSL(fstream& f, strlength& SL)
{
	int i = 0;
	char s;
	while (1) {
		f >> s;
		if (s == '\n' || f.eof()) {
			break;
		}
		if (s != '\n') {
			SL.A[i] = s;
			i++;
		}
		if (i >= N) { while ((s != '\n') && (!f.eof())) f >> s; break; }
	}
	SL.L = i;
}

void inputSL(strlength& SL)
{
	char s = getchar();
	int i = 0;
	do
	{
		SL.A[i] = getchar();
		if (SL.A[i] == '\n' || SL.A[i] == ' ') break;
		i++;
	} while (true);
	SL.L = i;
}

void outputSL(fstream& of, strlength SL) {
	int i = 0;
	while (i < SL.L) {
		of << SL.A[i];
		i++;
	}
	of << " ";
}

void outputSL(strlength SL) {
	int i = 0;
	while (i < SL.L) {
		cout << SL.A[i];
		i++;
	}
	cout << " ";
}

bool isEqual(strlength str1, strlength str2) {
	int i = 0;
	if (str1.L != str2.L) return false;
	else while (i < str1.L) if (str1.A[i] != str2.A[i++]) return false;
	return true;
}
