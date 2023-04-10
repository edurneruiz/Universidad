#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int libro_perdido(vector<int> const& v, int ini, int fin) {
	if (ini == fin)
		return ini;
	else {
		int mitad = (ini + fin) / 2;

		if (v[mitad - 1] != v[mitad] && v[mitad] != v[mitad + 1])
			return mitad;

		if (mitad % 2 == 0) { // 1 1 2 2 9, mitad 2, 1 2 2 9 9
			if (v[mitad - 1] == v[mitad])
				return libro_perdido(v, ini, mitad);
			else if (v[mitad] == v[mitad + 1])
				return libro_perdido(v, mitad, fin);
		}
		else { // 1 1 2 -2- 3 3 9, 1 1 2 -3- 3 9 9
			if (v[mitad - 1] == v[mitad])
				return libro_perdido(v, mitad + 1, fin);
			else if (v[mitad] == v[mitad + 1])
				return libro_perdido(v, ini, mitad - 1);
		}

	}

}


int libroperdido(vector<int> const& v, int ini, int fin) {
	if (fin - ini == 1) {
		if (ini == 0) {
			if (v[ini] == v[fin])
				return fin + 1;
			else
				return ini;
		}
		if (fin == v.size() - 1) {
			if (v[ini] == v[fin])
				return ini - 1;
			else
				return fin;
		}
	}
	else {
		int mitad = (ini + fin) / 2;

		if (mitad == 0 && v[mitad] != v[mitad + 1])
			return mitad;
		else if (mitad == v.size() - 1 && v[mitad - 1] != v[mitad])
			return mitad;
		else if (v[mitad - 1] != v[mitad] && v[mitad] != v[mitad + 1])
			return mitad;
		else if (mitad % 2 == 0) {
			if (v[mitad - 1] == v[mitad])
				return libroperdido(v, ini, mitad);
			else if (v[mitad] == v[mitad + 1])
				return libroperdido(v, mitad, fin);
		}
		else {
			if (v[mitad - 1] == v[mitad])
				return libroperdido(v, mitad, fin);
			else if (v[mitad] == v[mitad + 1])
				return libroperdido(v, ini, mitad);
		}
	}
}

bool resuelveCaso() {
	int n, aux;
	cin >> n;

	if (!std::cin)
		return false;

	vector<int> v;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		v.push_back(aux);
	}

	cout << libro_perdido(v, 0, v.size() - 1) << '\n';
	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos) {
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}