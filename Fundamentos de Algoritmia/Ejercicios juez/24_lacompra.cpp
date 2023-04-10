#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void comprar_productos(int m, int n, int producto, vector<vector<int>> const& pxsxp, vector<int> & pxs,
					   int & p, int & pmin, vector<int> const& minimos) {

	for (int supermercado = 0; supermercado < m; ++supermercado) {
		if (pxs[supermercado] < 3) { //si no hemos comprado ya tres productos en ese supermercado
			++pxs[supermercado];
			p += pxsxp[supermercado][producto];

			if (producto == n - 1)
				pmin = fmin(p, pmin);
			else {
				if (p + minimos[producto] <= pmin) //estimamos
					comprar_productos(m, n, producto + 1, pxsxp, pxs, p, pmin, minimos);
			}
				
			--pxs[supermercado];
			p -= pxsxp[supermercado][producto];
		}
	}
}

void resuelveCaso() {
	int m, n, p = 0, pmin = 2147483647, acum = 0;
	cin >> m >> n;
	vector<vector<int>> pxsxp(m, vector<int>(n));
	vector<int> pxs(m), minimos(n), acumulados(n);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			cin >> pxsxp[i][j];
	}
	for (int i = 0; i < n; ++i) { //cojo el supermercado j donde es más barato el producto i
		int min = pxsxp[0][i];
		for (int j = 0; j < m; ++j) {
			minimos[i] = fmin(min, pxsxp[j][i]);
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		acumulados[i] = acum;
		acum += acumulados[i];
	}

	comprar_productos(m, n, 0, pxsxp, pxs, p, pmin,acumulados);
	if (pmin == 2147483647)
		cout << "Sin solucion factible" << '\n';
	else
		cout << pmin << '\n';
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos) {
		resuelveCaso();
		--numCasos;
	}
	return 0;
}