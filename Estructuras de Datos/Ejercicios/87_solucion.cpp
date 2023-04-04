#include <iostream>
#include <vector>
#include "set_eda.h"
using namespace std;

typedef struct {
	bool b;
	int n;
} tPar;

//funciones
bool resuelveCaso();

int main() {
	while (resuelveCaso()) {}
	return 0;
}

bool resuelveCaso() {
	int n, m;
	cin >> n >> m;
	if (!std::cin) return false;

	set<int> c;
	int aux, lower, upper;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		c.insert(aux);
	}
	for (int i = 0; i < m; ++i) {
		cin >> lower >> upper;
		cout << c.count_interval(lower, upper) << "\n";
	}
	cout << "---\n";
	return true;
}
