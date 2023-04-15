///EDURNE RUIZ DG33
/*
La Unidad Curiosa de Monitorizaci´on (UCM) se encarga de leer los datos proporcionados por una serie de sensores y enviar con 
cierta periodicidad los datos obtenidos y procesados a los usuarios que se han registrado previamente. La UCM admite que los 
usuarios se registren proporcionando un Identificador, un n´umero entre 103 y 109 que identifica de forma ´unica al usuario, 
y un Periodo, el intervalo de tiempo que transcurrir´a entre dos env´ıos consecutivos de informaci´on a ese usuario (entre 1 
y 5.000). Es decir, cuando hayan pasado Periodo segundos desde que el usuario se registr´o, este recibir´a la informaci´on de 
la UCM por primera vez; y despu´es recibir´a la informaci´on cada Periodo segundos.
Acaban de registrarse varios usuarios, todos con identificadores dintintos. ¿Podr´ıas decir a qui´enes ir´an dirigidos los K 
primeros env´ıos de informaci´on? Si dos o m´as usuarios tienen que recibir la informaci´on al mismo tiempo, los env´ıos se 
realizan en orden creciente de sus identificadores de usuario.
*/

#include <iostream>
#include "PriorityQueue.h"
#include <fstream>
using namespace std;

typedef struct {
	int id;
	int periodo;
	int momento;
} tCliente;

bool operator< (tCliente const& c1, tCliente const& c2) {
	return c1.momento < c2.momento || ((c2.momento == c1.momento) && c1.id < c2.id);
}

void k_envios(int k, PriorityQueue<tCliente> & registros) {
	tCliente act;
	while (k != 0) {
		act = registros.top();
		registros.pop();
		cout << act.id << '\n';
		act.momento += act.periodo;
		registros.push(act);
		--k;
	}
}

bool resuelveCaso() {
	int nelems;
	cin >> nelems;

	if (nelems == 0)
		return false;
	else {
		PriorityQueue<tCliente> registros; int idaux, periodoaux, k;
		for (int i = 0; i < nelems; ++i) { //insertar en el conjunto
			cin >> idaux >> periodoaux;
			registros.push({ idaux, periodoaux, periodoaux });
		}
		cin >> k;
		k_envios(k, registros);
		cout << "--- \n";

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada :
2
1234 200
9000 300
5
0

salida:
1234
9000
1234
1234
9000
---

*/
