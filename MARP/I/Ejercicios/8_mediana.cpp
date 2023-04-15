///EDURNE RUIZ DG33
/*
En la carnicer´ıa de mi pueblo tienen un sistema muy particular para decidir el orden en el que los clientes que est´an 
esperando son atendidos. Cuando un cliente llega a la tienda recoge un n´umero que es distinto a todos los dem´as repartidos 
ese d´ıa y espera pacientemente a ser atendido.
Cuando el carnicero, que estudia matem´aticas los fines de semana, puede atender a otro cliente, grita “¿El mediano, por 
favor?”, esperando que aquel cliente cuyo n´umero sea la mediana en ese momento d´e un paso al frente y empiece a comprar. 
M´as formalmente, la mediana de N elementos es el elemento que ocupar´ıa la posici´on b(N + 1)/2c si estos se ordenaran
crecientemente.
Como el proceso en ocasiones produce un gran alboroto entre la clientela, quiere un programa que le muestre cada vez el n´umero del siguiente cliente que debe ser atendido. ¿Puedes ayudarle?*/

#include <iostream>
#include "PriorityQueue.h"
#include "TreeSet_AVL.h"
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

void sucesion_eventos(Set<int> & f) {
	int c;
	cin >> c;

	if (c == 0) {
		if (f.empty())
			cout << "ECSA ";
		else {
			int m = (f.size() + 1) / 2;
			int mediana = f.kesimo(m);

			cout << mediana << " ";
			f.erase(mediana);
		}
	}
	else {
		f.insert(c);
	}
}

bool resuelveCaso() {
	int eventos;
	cin >> eventos;

	if (!std::cin)
		return false;
	else {
		Set<int> f;

		while (eventos--) {
			sucesion_eventos(f);
		}
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
7
1 15 7 0 20 0 0

6
0 14 8 2 23 0
salida:
7 15 1

ECSA 8

*/