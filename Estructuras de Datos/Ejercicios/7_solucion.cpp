//EDURNE RUIZ, DG28

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "pila.h"
using namespace std;

struct Accidente {
	string fecha;
	int muertos;
};

Accidente nuevoAccidente(string fecha, int muertos) {
	Accidente a;
	a.fecha = fecha;
	a.muertos = muertos;
	return a;
}

void anterior(stack<Accidente>& _acc) {
	stack<Accidente> anteriores;
	int i = 0;
	
	anteriores.push(_acc.top());  
	_acc.pop();
	cout << "NO HAY" << "\n"; //para el primer caso, nunca va a haber un accidente anterior con más muertos

	while (!_acc.empty()) {
		if (_acc.top().muertos >= anteriores.top().muertos) {
			while (!anteriores.empty() && _acc.top().muertos >= anteriores.top().muertos) anteriores.pop();
			if (!anteriores.empty()) cout << anteriores.top().fecha << '\n';
			else cout << "NO HAY\n";
		}
		else cout << anteriores.top().fecha << '\n'; 
		anteriores.push(_acc.top());
		_acc.pop();
	}

}

bool resuelveCaso() {
	int numAccidentes, maux;
	string faux;

	cin >> numAccidentes;
	if (!std::cin) return false;
	
	vector<Accidente> acc(numAccidentes);
	stack<Accidente> _acc;
	for (int i = 0; i < numAccidentes; i++) { // leer los datos 
		cin >> faux >> maux;
		acc[i] = nuevoAccidente(faux, maux);
	}
	for (int i = numAccidentes - 1; i >= 0; i--) _acc.push(acc[i]);

	anterior(_acc);
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}