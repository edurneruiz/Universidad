#include <iostream>
#include "hashmap_eda.h"
using namespace std;



bool todoImpares(unordered_map<int, int>& m) {
	auto it = m.begin();
	while (it != m.end()) {
		if (it->clave % 2 == 0) 
			return false;
		else ++it;
	}
	return true;
}

void eliminarPares(unordered_map<int, int>& m) {
	auto it = m.begin();
	while (it != m.end()) {
		if (it->clave % 2 == 0) 
			it = m.erase(it);
		else ++it;
	}
}

bool resuelveCaso() {
	int nClaves, aux;
	cin >> nClaves;
	if (nClaves == 0) return false;

	unordered_map<int, int> claves;
	for (int i = 0; i < nClaves; ++i) {
		cin >> aux;
		claves[aux];
	}

	eliminarPares(claves);
	if (todoImpares(claves)) cout << "TODO BIEN \n";
	else return false;

	return true;
}

int main() {
	while (resuelveCaso()){}
	return 0;
}