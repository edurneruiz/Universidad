#include <iostream>
#include "lista_enlazada.h"
using namespace std;

bool resuelveCaso() {
	int n, pos, aux;

	cin >> n >> pos;
	if (!std::cin) return false;

	list<int> l;
	while (n > 0) {
		cin >> aux;
		l.push(aux);
		--n;
	}

	try { 
		l.llevarAlPrincipio(pos); 
		l.print();
	}
	catch (domain_error e) { cout << e.what() << "\n"; }

	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}