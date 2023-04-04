//Aitor Esteban Nתסez

#include <iostream>
#include <string>
#include <fstream>
#include "deque_eda.h"
#include "stack_eda.h"

using namespace std;

void mezclar(stack<char>& a, stack<char> &b, deque<char> &q) {
	while (!b.empty()) {
		a.push(b.top());
		b.pop();
	}
	while (!a.empty()) {
		q.push_front(a.top());
		a.pop();
	}
}

deque<char> fase2inversa(string code) {
	deque<char> X;
	stack<char> a, b;
	int i = 0;
	while (i < code.size()) {
		if ((i % 2) == 0)  a.push(code[i]);
		else b.push(code[i]);
		i++;
	}
	mezclar(a, b, X);
	return X;
}

void volcar_pila(stack<char> & pila, deque<char> & dcola) {
	while (!pila.empty()) {
		dcola.push_back(pila.top());
		pila.pop();
	}
}

bool es_vocal(char letra) {
	return  (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u' || letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U');
}

deque<char> fase1inversa(deque<char> &q) {

	deque<char> n;
	stack<char> pila_consonantes; // para darles la vuelta
	while (!q.empty()) {
		char c = q.front();
		q.pop_front();
		if (es_vocal(c)) {
			volcar_pila(pila_consonantes, n);
			n.push_back(c);
		}
		else {
			pila_consonantes.push(c);
		}
	}
	volcar_pila(pila_consonantes, n);


	return n;
}


bool resuelveCaso() {

	string code;
	getline(cin, code);

	if (!std::cin) return false;

	deque<char> s = fase2inversa(code);
	s = fase1inversa(s);

	while (!s.empty()) {
		cout << s.front();
		s.pop_front();
	}

	cout << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero

	while (resuelveCaso());
	system("PAUSE");

	return 0;
}