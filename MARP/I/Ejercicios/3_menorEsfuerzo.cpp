///EDURNE RUIZ DG33
/*Johnny Calculin sabe sumar numeros mentalmente a gran velocidad, pero el esfuerzo que le supone realizar una suma depende 
del valor de los sumandos. En concreto, sumar a más b le supone un esfuerzo igual a a + b. Cuando tiene que sumar mas de dos 
numeros la cosa se complica, ya que el orden en que va realizando las sumas afectan al esfuerzo total empleado.
Johnny se esta preparando para un concurso de sumas y quiere averiguar como deberia ir sumando los n´umeros para necesitar 
el minimo esfuerzo. ¿Puedes ayudarle?
*/

#include <iostream>
#include "PriorityQueue.h"
#include <fstream>
using namespace std;

long long int esfuerzo_minimo(PriorityQueue<long long int> & sumandos) {
	long long int a, b, esfuerzo = 0;
	
	while (!sumandos.empty()) {
		a = sumandos.top();
		sumandos.pop();
		if (!sumandos.empty()) {
			b = sumandos.top();
			sumandos.pop();
			esfuerzo += (a + b);
			sumandos.push(a + b); 
		}
	}
	return esfuerzo;
}

bool resuelveCaso() {
	int nelems;
	cin >> nelems;

	if (nelems == 0)
		return false;
	else {
		PriorityQueue<long long int> sumandos; int aux;
		for (int i = 0; i < nelems; ++i) { //insertar en el conjunto
			cin >> aux;
			sumandos.push(aux);
		}
		cout << esfuerzo_minimo(sumandos) << '\n';

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada: 
3
1 2 3
4
3 1 4 2
4
30 40 50 60
1
5
0

salida:
9
19
360
0


*/