#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "pila.h"
using namespace std;

bool abierto(char c) { return (c == '(') || (c == '[') || (c == '{'); }
bool cerrado(char c) { return (c == ')') || (c == ']') || (c == '}'); }
bool iguales(char abierto, char cerrado) {
	return (abierto == '(' && cerrado == ')') || (abierto == '[' && cerrado == ']') || (abierto == '{' && cerrado == '}');
}

bool equilibrada(string frase) {
	stack<char> abiertos, cerrados;

	for (char c : frase) {
		if (abierto(c)) abiertos.push(c); //si es un paréntesis abierto, lo añado a la pila 
		else if (cerrado(c)) { 
			cerrados.push(c); //añado a la pila el cerrado
			if (abiertos.empty()) return false; //si hay un cerrado y no hay abiertos, está mal equilibrado
			else {
				if (iguales(abiertos.top(), cerrados.top())) { //si los paréntesis son del mismo tipo, los elimino de las pilas
					abiertos.pop(); 
					cerrados.pop();
				}
				else return false; //si los paréntesis no son del mismo tipo, está mal equilibrado
			}
		}
	}

	return (abiertos.size() == 0 && cerrados.size() == 0);
}

bool resuelveCaso() {
	string frase;
	getline(cin, frase);

	if (!std::cin) return false;

	if (equilibrada(frase)) cout << "SI\n";
	else cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}