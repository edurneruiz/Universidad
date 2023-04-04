#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
using namespace std;

//funciones
void print(queue<char>& may);
void descodificarPrimerPaso(queue<char>& mensaje);
void descodificarSegundoPaso(queue<char>& mensaje);
bool vocal(char may);
void annadirConsonantes(queue<char>& m, stack<char>& c);

bool resuelveCaso() {
	queue<char> mensaje;
	string m;
	getline(cin, m);

	if (!std::cin) return false;
	for (char may : m) mensaje.push(may);
	descodificarPrimerPaso(mensaje);
	descodificarSegundoPaso(mensaje);
	print(mensaje);

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

void descodificarPrimerPaso(queue<char>& mensaje) {
	int i = 0;
	queue<char> delante;
	stack<char> atras;

	while (!mensaje.empty()) {
		if (i % 2 == 0) { delante.push(mensaje.front()); }
		else atras.push(mensaje.front());
		mensaje.pop();
		++i;
	}
	while (!delante.empty()) {
		mensaje.push(delante.front());
		delante.pop();
	}
	while (!atras.empty()) {
		mensaje.push(atras.top());
		atras.pop();
	}
}

void descodificarSegundoPaso(queue<char>& mensaje) {
	stack<char> consonantes;
	int size = mensaje.size(), i = 0;

	while (i < size) {
		if (vocal(mensaje.front())) {
			annadirConsonantes(mensaje, consonantes);
			mensaje.push(mensaje.front());
		}
		else { consonantes.push(mensaje.front()); }
		mensaje.pop();
		++i;
	}
	annadirConsonantes(mensaje, consonantes);

}

void annadirConsonantes(queue<char>& m, stack<char>& c) {
	while (!c.empty()) {
		m.push(c.top());
		c.pop();
	}
}

bool vocal(char c) { 
	char may = toupper(c);
	return ((may == 'A') || (may == 'E') || (may == 'I') || (may == 'O') || (may == 'U')); 
}

void print(queue<char>& may) {
	while (!may.empty()) {
		cout << may.front();
		may.pop();
	}
	cout << '\n';
}