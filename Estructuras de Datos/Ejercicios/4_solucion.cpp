//EDURNE RUIZ. DG28

#include <iostream>
#include <vector>
#include <fstream>
#include "4_polinomios.h"
using namespace std;


bool resuelveCaso() {
	int num_valores, valor_aux, coef_aux, exp_aux;
	polinomio pm;
	cin >> coef_aux >> exp_aux;

	if (!std::cin) return false;

	while (!(coef_aux == 0 && exp_aux == 0)) { //añado los datos al polinomio
		pm.add(coef_aux, exp_aux);
		cin >> coef_aux >> exp_aux;
	}

	cin >> num_valores;
	for (int j = 0; j < num_valores; j++) {
		cin >> valor_aux;
		cout << pm.evaluate(valor_aux) << " ";
	}
	cout << "\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}