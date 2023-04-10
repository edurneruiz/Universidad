#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void asignar_trabajos(int n, int func, vector<vector<int>> const& txfxt, int & t, int & tmin,
					  vector<bool> & asignados, vector<int> const& acumulados) {
	for (int trabajo = 0; trabajo < n; ++trabajo) {
		if (!asignados[trabajo]) {
			t += txfxt[func][trabajo];
			asignados[trabajo] = true;

			if (func == n - 1)
				tmin = fmin(t, tmin);
			else
				if (t + acumulados[func] < tmin)
					asignar_trabajos(n, func + 1, txfxt, t, tmin, asignados, acumulados);

			t -= txfxt[func][trabajo];
			asignados[trabajo] = false;
		}
	}
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;
	else {
		int t = 0, tmin = 10000, acum = 0;
		vector<vector<int>> txfxt(n, vector<int>(n));
		vector<bool> asignados(n, false);
		vector<int> minimos(n), acumulados(n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> txfxt[i][j];
		}
		for (int i = 0; i < n; ++i) { //cojo el funcionario j q hace en menos tiempo el trabajo i
			int min = txfxt[0][i];
			for (int j = 0; j < n; ++j) {
				min = fmin(min, txfxt[j][i]);
			}
			minimos[i] = min;
		}
		for (int i = n - 1; i >= 0; --i) {
			acumulados[i] = acum;
			acum += acumulados[i];
		}

		asignar_trabajos(n, 0, txfxt, t, tmin, asignados, acumulados);
		cout << tmin << '\n';

		return true;
	}

}

int main() {
	while(resuelveCaso()) {}
	return 0;
}