/*
Consideremos una matriz, M, de números reales de dimensiones N * N. Supongamos que esta matriz 
nos sirve para cartografiar cierto terreno que se ha dividido en forma de cuadrícula, de forma que
M[i][j] es la altura media de la casilla (i,j). Se desea construir una carretera entre dos puntos 
dados. Para que una carretera pueda unir dos casillas adyacentes (no en diagonal) es necesario que 
la diferencia entre sus alturas medias no supere cierto valor, hmar, es decir:
| M[a][6] – M[c][d] | <hmax donde las casillas (a,b) y (c,d) son adyacentes. 
Dada una matriz M, una altura máxima hmax y dos casillas del terreno distintas entre sí, 
diseña un algoritmo de vuelta atrás que calcule la carretera de menor longitud (si es que existe) 
que resuelva el problema. Se considera que la longitud de la carretera es el número de casillas 
por las que pasa, incluyendo tanto el origen como el destino.
*/
#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
using namespace std;
typedef struct {
	int x;
	int y;
} casilla;

int operator==(casilla c1, casilla c2) {
	return c1.x == c2.x && c1.y == c2.y;
}

bool desnivel_permitido(vector<vector<int>> const& terreno, casilla actual, casilla anterior, int hmax) {
	int alt_act, alt_ant = terreno[anterior.x][anterior.y];
	if (alt_ant == -INT_MAX)
		alt_ant = 0;
	else if (alt_ant < 0)
		alt_ant = terreno[anterior.x][anterior.y] * (-1);
	alt_act = terreno[actual.x][actual.y];
	return abs(alt_act - alt_ant) <= hmax;
}

void crear_carretera(int n, int hmax, casilla const& destino, casilla actual, casilla anterior, 
					 vector<vector<int>> & terreno, int & lng, int & lng_min) {

	if (desnivel_permitido(terreno, actual, anterior, hmax)) {
		++lng;
		if (terreno[actual.x][actual.y] != 0)
			terreno[actual.x][actual.y] = terreno[actual.x][actual.y] * (-1); //marcamos q pasamos x ahí
		else
			terreno[actual.x][actual.y] = - INT_MAX;

		if (actual == destino)
			lng_min = fmin(lng, lng_min);
		else {
			if (actual.x != 0 && terreno[actual.x - 1][actual.y] >= 0)//para arriba
				crear_carretera(n, hmax, destino, { actual.x - 1, actual.y }, actual,
					terreno, lng, lng_min);

			if (actual.x != n - 1 && terreno[actual.x + 1][actual.y] >= 0) // para abajo
				crear_carretera(n, hmax, destino, { actual.x + 1, actual.y }, actual,
					terreno, lng, lng_min);
			
			if (actual.y != 0 && terreno[actual.x][actual.y - 1] >= 0) //para izquierda
				crear_carretera(n, hmax, destino, { actual.x, actual.y - 1 }, actual,
					terreno, lng, lng_min);
			
			if (actual.y != n - 1 && terreno[actual.x][actual.y + 1] >= 0) //para derecha
				crear_carretera(n, hmax, destino, { actual.x, actual.y + 1 }, actual,
					terreno, lng, lng_min);
		}
		--lng;
		if (terreno[actual.x][actual.y] != - INT_MAX)
			terreno[actual.x][actual.y] = terreno[actual.x][actual.y] * (-1); 
		else
			terreno[actual.x][actual.y] = 0; //desmarcamos q pasamos x ahí
	}
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;
	else {
		int hmax, lng = 0, lng_min = INT_MAX;
		casilla origen, destino;
		cin >> hmax;
		cin >> origen.x >> origen.y >> destino.x >> destino.y;
		vector<vector<int>> terreno(n, vector<int>(n));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> terreno[i][j];
		}

		crear_carretera(n, hmax, destino, origen, origen, terreno, lng, lng_min);
		if (lng_min == INT_MAX)
			cout << "IMPOSIBLE \n";
		else
			cout << lng_min << "\n";

		return true;
	}
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
3 2
0 1
0 0
0 3 4
1 2 3
1 1 1

2 2
1 0
1 1
3 5
1 7

2 2
1 0
1 1
3 5
1 3

3 3
0 0
2 2
3 9 5
8 1 6
2 2 2

3 5
0 0
2 2
3 9 5
8 1 6
2 2 2

3 5
0 0
2 2
3 9 5
8 1 6
3 2 2

-> 4 : (0,1),(1,1),(1,0),(0,0)
-> 4
-> IMPOSIBLE
-> IMPOSIBLE
-> 5
*/