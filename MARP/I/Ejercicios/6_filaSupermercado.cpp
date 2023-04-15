///EDURNE RUIZ DG33
/*
Según la estimación de cuánto tardará cada cliente en pasar por la caja en base a la cantidad de productos en el carrito y 
averiguar entonces en qué caja le tocará pagar.
Ten en cuenta que las cajas están numeradas de la 1 a la N y que en caso de quedar dos cajas libres
a la vez, el primer cliente irá a la caja con menor número.
*/

#include <iostream>
#include "PriorityQueue.h"
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

typedef struct {
	int caja; //caja ocupada por el cliente
	int segundos; //segundos que el cliente está pagando
} tCaja;

bool operator< (tCaja const& c1, tCaja const& c2) {
	return c1.segundos < c2.segundos || (c1.segundos == c2.segundos && c1.caja < c2.caja);
}

int cajero_disponible(int cajas, int clientes, PriorityQueue<tCaja>& cajeros) {
	int cj = 1, seg_aux;

	while (clientes > 0) {
		cin >> seg_aux;

		if (cj <= cajas)			//si aún no se han ocupado todas las cajas disponibles
			cajeros.push({ cj++, seg_aux });
		else {								//se han ocupado ya todas las cajas -> se ocupa la que termine antes
			tCaja libre = cajeros.top();
			cajeros.pop();
			cajeros.push({ libre.caja, libre.segundos + seg_aux });
		}
		--clientes;
	}

	return (cajeros.size() < cajas) ? cj : cajeros.top().caja;
}

bool resuelveCaso() {
	int cajas, clientes;
	cin >> cajas >> clientes;

	if (cajas == 0 && clientes == 0)
		return false;
	else {
		PriorityQueue<tCaja> cajeros;
		cout << cajero_disponible(cajas, clientes, cajeros) << '\n';
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada :
2 2
10 5

2 2
5 10

3 2
5 10

8 10
26 15 47 6 20 18 33 16 12 9

5 5
12 13 14 15 12

0 0

salida:
2
1
3
8
1
*/