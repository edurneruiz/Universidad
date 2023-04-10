#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void limpiar_carreteras(int n, int m, int maquina, vector<int> const& c_anch, vector<int> const& q_anch,
						vector<vector<int>> const& cxmxc, int & c, int & cmax, 
						vector<bool> & limpias, vector<int> const& acums) {
	
	for (int carretera = 0; carretera < n; ++carretera) {
		if (!limpias[carretera] && c_anch[carretera] >= q_anch[maquina]) {
			c += cxmxc[maquina][carretera];
			limpias[carretera] = true;

			if (maquina == m - 1)
				cmax = fmax(c, cmax);
			else
				if(c + acums[maquina + 1] > cmax)
					limpiar_carreteras(n, m, maquina + 1, c_anch, q_anch, cxmxc, c, cmax, limpias, acums);

			c -= cxmxc[maquina][carretera];
			limpias[carretera] = false;
		}
	}

}

void resuelveCaso() {
	int n, m;
	cin >> m >> n;

	vector<vector<int>> cxmxc(m, vector<int>(n));
	vector<int> c_anch(n), q_anch(m), maximos(n), acums(n);

	for (int i = 0; i < m; ++i) {
		cin >> q_anch[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> c_anch[i];
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> cxmxc[i][j];
		}
	}
	
	for (int i = 0; i < n; i++) {
		int max = cxmxc[0][i];
		for (int j = 1; j < m; j++) {
			if (cxmxc[j][i] > max)
				max = cxmxc[j][i];
		}
		maximos[i] = max;
	}
	int aux = 0;
	for (int i = n - 1; i >= 0; i--) {
		aux += maximos[i];
		acums[i] = aux;
	}
	int c = 0, cmax = 0; vector<bool> limpias(n, false);
	limpiar_carreteras(n, m, 0, c_anch, q_anch, cxmxc, c, cmax, limpias, acums);
	cout << cmax << '\n';
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