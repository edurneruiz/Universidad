#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//devuelve -1 si esta en tramo decreciente, 0 si es el minimo, 1 si está en tramo creciente
int tipo_tramo(vector<int> const& v, int pos) {
	if (v.size() == 1)
		return 0;
	else if (pos == 0)
		return (v[pos] > v[pos + 1]) ? -1 : 0;
	else if (pos == v.size() - 1) 
		return (v[pos] > v[pos - 1]) ? 1 : 0;
	else {
		if (v[pos - 1] > v[pos] && v[pos] < v[pos + 1])
			return 0;
		else if (v[pos - 1] > v[pos] && v[pos] > v[pos + 1])
			return -1;
		else if (v[pos - 1] < v[pos] && v[pos] < v[pos + 1])
			return 1;
	}
}

int minimovector(vector<int> const& v, int ini, int fin) {
	if (fin - ini == 1)
		return fmin(v[ini], v[fin]);
	else {
		int mitad = (ini + fin) / 2;
		int tt = tipo_tramo(v, mitad);

		if (tt == 0) return v[mitad];
		else if (tt == -1) return minimovector(v, mitad, fin);
		else if (tt == 1) return minimovector(v, ini, mitad);
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

	cout << minimovector(v, 0, v.size() - 1) << '\n';
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

/*
5
7 5 3 8 9
8
9 8 7 6 5 4 3 2
1
2
2
3 5
10
34 25 12 10 9 8 7 6 5 9

*/