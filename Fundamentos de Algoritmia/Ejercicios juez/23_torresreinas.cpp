#include<iostream>
#include <vector>
using namespace std;
using par = std::pair<int, int>;

/*
en un tablero de n x n

c_amen : en la posición i-ésima dice si la columna i está amenazada / ocupada ya -> es de tamaño n
d_amen : en la posición i-ésima dice si la diagonal i está amenazada ya -> es de tamaño 4n - 2
d_ocup : en la posición i-ésima dice si la diagonal i ya está ocupada -> tamaño 4n - 2
*/
///unir d_amen y d_ocup haciendolo de enteros 0 libre 1 ocupada 2 amenzada
void combinaciones_tablero(int n, int fila, int torres, int reinas, vector<vector<bool>> const& cinv, int & comb, vector<bool> & c_amen, 
							vector<bool> & d_amen, vector<bool> & d_ocup) {
	if (torres != 0) { //coloco torre
		for (int col = 0; col < n; ++col) { //voy cambiando su posición horizontalmente (sigue en la misma fila)
			//si esa casilla no está invadida ni amenazada anteriormente
			if (!cinv[fila - 1][col] && !c_amen[col] && !d_amen[col - fila + n + 1] 
				&& !d_amen[fila + col + 2*n - 1]) { 
				--torres;
				c_amen[col] = true; 
				d_ocup[col - fila + n + 1] = true;
				d_ocup[fila + col + 2 *n - 1] = true;

				if (fila == n)
					++comb;
				else
					combinaciones_tablero(n ,fila + 1, torres, reinas, cinv, comb, c_amen, d_amen, d_ocup);

				++torres;
				c_amen[col] = false;
				d_ocup[col - fila + n + 1] = false;
				d_ocup[fila + col + 2 *n - 1] = false;
			}
		}
	}

	if (reinas != 0) { //coloco reina
		for (int col = 0; col < torres + reinas; ++col) { //voy cambiando su posición horizontalmente (sigue en la misma fila)
			//si esa casilla no está invadida ni ocupada anteriormente
			if (!cinv[fila - 1][col] && !c_amen[col] && !d_ocup[col - fila + (n) + 1]
				&& !d_ocup[fila + col + 2*n - 1]) {
				--reinas;
				c_amen[col] = true;
				d_ocup[col - fila + (n) + 1] = true; 	
				d_amen[col - fila + (n) + 1] = true;
				d_ocup[fila + col + 2 * n - 1] = true;
				d_amen[fila + col + 2 * n - 1] = true;

				if (fila == n)
					++comb;
				else
					combinaciones_tablero(n, fila + 1, torres, reinas, cinv, comb, c_amen, d_amen, d_ocup);

				++reinas;
				c_amen[col] = false;
				d_ocup[col - fila + (n) + 1] = false;
				d_amen[col - fila + (n) + 1] = false;
				d_amen[fila + col + 2 *n - 1] = false;
				d_ocup[fila + col + 2 *n - 1] = false;
			}
		}
	}
}

bool resuelveCaso() {
	int torres;
	cin >> torres;

	if (!std::cin)
		return false;
	else {
		int reinas, invalidas, x, y, comb = 0;
		cin >> reinas >> invalidas;
		vector<vector<bool>> c_inv(torres + reinas, vector<bool>(torres+ reinas, false)); 
		vector<bool> c_amen(torres + reinas, false), d_amen(4*(torres + reinas) - 2, false), d_ocup(4 * (torres + reinas) - 2, false);
		while (invalidas) {
			cin >> x >> y;
			c_inv[x][y] = true;
			--invalidas;
		}

		combinaciones_tablero(torres + reinas, 1, torres, reinas, c_inv, comb, c_amen, d_amen, d_ocup);
		cout << comb << "\n --- \n";

		return true;
	}
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}