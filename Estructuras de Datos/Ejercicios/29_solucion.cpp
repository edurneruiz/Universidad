#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "treemap_eda.h"
using namespace std;
using clave_valor = std::pair<int, int>;

//funciones
int distintosConsecutivos(int n);

bool resuelveCaso() {
	int caps;

	cin >> caps;
	if (!std::cin) return false;
	cout << distintosConsecutivos(caps) << '\n';

	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;

	while (numCasos != 0) { 
		resuelveCaso(); 
		--numCasos;
	}
	system("pause");
	return 0;
}

int distintosConsecutivos(int n) {
	map<int, int> caps;
	string s;
	int c = 0, cmax = 0;

	getline(cin, s);
	getline(cin, s);
	for (int i = 0; i < n; ++i) {
		if (caps.count(s[2*i])) {
			c = 0;
			if (cmax > n - i) return cmax; //si es mayor el nº de caps sin repetir que el nº de los que quedan por revisar
		}
		else {
			caps.insert(s[2 * i]);
			++c;
			cmax = fmax(cmax, c);
		}
	}

	return cmax;
}

