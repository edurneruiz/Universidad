#include <iostream>
#include "lista_edurchan.h"
using namespace std;

bool resuelveCaso() {
	int n, pos, aux, dist;

	cin >> n;
	if (!std::cin) return false;

	eLista<int> l;
	while (n > 0) {
		cin >> aux;
		l.push(aux);
		--n;
	}
	cin >> pos >> dist;
	try {
		l.desplaza(pos, dist);
		l.print();
	}
	catch (domain_error e) { cout << e.what() << "\n"; }
	cout << "---\n";


	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}