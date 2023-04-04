#include<iostream>
#include "deque_eda.h"
#include "nueva_deque.h"
using namespace std;


void print(dcola<int> & d) {
	while (!d.empty()) {
		cout << d.front() << " ";
		d.pop_front();
	}
	cout << "\n";
}

bool resuelveCaso() {
	int n, m, aux;

	cin >> n;
	if (!std::cin) return false;

	dcola<int> principal, secundaria;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		principal.push_back(aux);
	}
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> aux;
		secundaria.push_back(aux);
	}
	principal.entremezclar(secundaria);
	print(principal);
	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos != 0) {
		resuelveCaso();
		--numCasos;
	}
	return 0;
}