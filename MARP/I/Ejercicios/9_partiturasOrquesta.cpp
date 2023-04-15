///EDURNE RUIZ DG33
/*
Para una orquesta modesta, gran parte del presupuesto se va en la compra de las partituras. Si cada m´usico tiene su propia copia, el
n´umero puede ascender a m´as de 100. Afortunadamente, los m´usicos que tocan el mismo instrumento se sientan juntos y pueden compartir 
atril. Eso supone un ahorro considerable, aunque si se abusa demasiado puede provocar un efecto feo en la sala de conciertos. Al fin y 
al cabo ver a muchos m´usicos agolp´andose alrededor del mismo atril no es muy est´etico.
La secci´on de asuntos econ´omicos de la orquesta nos ha informado del n´umero de partituras que podremos comprar para la pr´oxima obra
que se tocar´a. Teniendo en cuenta el n´umero de m´usicos de cada instrumento, ¿cu´al ser´a el atril m´as concurrido?
*/

#include <iostream>
#include "PriorityQueue.h"
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int atril_mas_concurrido(int p, PriorityQueue<int, greater<int>> & partituras) {

	while (p--) {
		int mas_concurrido = partituras.top();
		int mitad = mas_concurrido / 2;

		partituras.pop();
		partituras.push(mitad);
		if (mas_concurrido % 2 == 0)
			partituras.push(mitad);
		else
			partituras.push(mitad + 1);
	}

	return partituras.top();
}

bool resuelveCaso() {
	int p, n;
	cin >> p >> n;

	if (!std::cin)
		return false;
	else {
		PriorityQueue<int, greater<int>> partituras; int aux, N = n;
		while (n--) {			
			cin >> aux;
			partituras.push(aux);
		}
		cout << atril_mas_concurrido(p - N, partituras) << '\n';
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
4 4
8 5 5 2

6 4
8 5 5 2

7 4
8 5 5 2

salida:
8

5

4
*/