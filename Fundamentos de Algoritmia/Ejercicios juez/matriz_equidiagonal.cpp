/*Una matriz cuadrada es equidiagonal si el producto de los elementos de su diagonal
principal es igual al producto de los elementos de su diagonal secundaria, y sus cuatro submatrices
son a su vez equidiagonales.*/
#include<iostream>
#include<vector>
using namespace std;
typedef struct {
	bool equidiagonal;
	int diagonal;
} info_matriz;

void print(info_matriz const& m) {
	if (m.equidiagonal)
		cout << "SI " << m.diagonal << "\n";
	else cout << "NO" << "\n";
}

info_matriz es_equidiagonal(int iniX, int finX, int iniY, int finY, vector<vector<int>> const& matriz) {
	if (iniX == finX)
		return { true, matriz[iniX][iniY] };
	else {
		int mitadX = (iniX + finX) / 2, mitadY = (iniY + finY) / 2;
		info_matriz c1 = es_equidiagonal(iniX, mitadX, iniY, mitadY, matriz);
		info_matriz c2 = es_equidiagonal(mitadX + 1, finX, iniY, mitadY, matriz);
		info_matriz c3 = es_equidiagonal(iniX, mitadX, mitadY + 1, finY, matriz);
		info_matriz c4 = es_equidiagonal(mitadX + 1, finX, mitadY + 1, finY, matriz);

		return { c1.equidiagonal && c2.equidiagonal && c3.equidiagonal && c4.equidiagonal
				&& (c1.diagonal*c4.diagonal == c2.diagonal*c3.diagonal),
				c1.diagonal*c4.diagonal };
	}
}

void resuelveCaso() {
	int N;
	cin >> N;
	vector<vector<int>> matriz(N, vector<int>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			cin >> matriz[i][j];
	}


	print(es_equidiagonal(0, N - 1, 0, N - 1, matriz));
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

/*
5
1
3
2
1 2
2 4
2
1 2
3 4
4
1 2 -1 3
2 4 1 3
0 2 5 7
0 6 0 0
4
1 2 6 2
2 4 9 3
0 2 5 7
0 6 0 0
*/