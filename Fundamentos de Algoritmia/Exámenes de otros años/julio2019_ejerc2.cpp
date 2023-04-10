#include<iostream>
#include<vector>
#include <cmath>
using namespace std;

const int MAX = 16;
typedef int tCuadricula[MAX][MAX];


bool equilibrado(int F, int C, int lab, tCuadricula& cuad) {

	if (F*C == 1) return true;
	else {
		int f = F / 2, c = C / 2, lab1 = 0, lab2 = 0, lab3= 0, lab4 = 0, i = 0, j = 0;
		tCuadricula c1, c2, c3, c4;
		bool eq, l, dif = true;
		for (int i = 0; i < f; i++) {
			for (int j = 0; j < c; j++) {
				c1[i][j] = cuad[i][j];
				c2[i][j] = cuad[i + f][j];
				c3[i][j] = cuad[i][j + c];
				c4[i][j] = cuad[i + f][j + c];
				lab1 = (c1[i][j] == 1) ? lab1+1 : lab1;
				lab2 = (c2[i][j] == 1) ? lab2+1 : lab2;
				lab3 = (c3[i][j] == 1) ? lab3+1 : lab3;
				lab4 = (c4[i][j] == 1) ? lab4+1 : lab4;
			}
		}
		eq = equilibrado(f, c, lab1, c1) && equilibrado(f, c, lab2, c2) && equilibrado(f, c, lab3, c3) && equilibrado(f, c, lab4, c4);
		l = (lab > 0.75*F*C) ? false : (lab < 0.25*F*C - 1) ? false : true;
		dif = (abs(lab1 - lab2) > 2) ? false : (abs(lab1 - lab3) > 2) ? false : (abs(lab1 - lab4) > 2) ? false : (abs(lab2 - lab3) > 2) ? false : (abs(lab2 - lab4) > 2) ? false : (abs(lab3 - lab4) > 2) ? false : true;
		return eq && l && dif;
	}

}

void resuelveCaso() {
	int F, C, lab = 0;
	cin >> F;
	C = F;
	tCuadricula c;
	for (int i = 0; i < F; i++) { 
		for (int j = 0; j < C; j++) {
			cin >> c[i][j];
			lab = (c[i][j] == 1) ? lab+1 : lab;
		}
	}
	if (equilibrado(F, C, lab, c)) cout << "SI" << endl;
	else cout << "NO" << endl;
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	system("pause");
	return 0;
}