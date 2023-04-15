#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
using tPeli = pair<int, int>;

bool noSolapan(int j, tPeli const& p) {
	return p.first + p.second + 10 <= j;
}

int rellenoTabla(int N, vector<tPeli> const& pelis) {
	vector<int> m(1451, 0); //1441 minutos al día + 10 de comprar palomitas

	for (int i = 1; i <= N; ++i) {
		for (int j = 1450; j > 0; --j) {
			if (noSolapan(j, pelis[i]))
				m[j] = fmax(m[j], m[pelis[i].first] + pelis[i].second);
		}
	}

	return m[1450];
}

bool resuelveCaso() {
	int N; cin >> N;

	if (!N)
		return false;

	vector<tPeli> pelis(N + 1);
	for (int i = 1; i <= N; ++i) {
		char c; int h, m; 
		cin >> h >> c >> m >> pelis[i].second;
		pelis[i].first = 60 * h + m;
	}

	sort(pelis.begin(), pelis.end());
	cout << rellenoTabla(N, pelis) << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos10.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()) {}
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
