#include "reparto.h"


//prototipos
void inicializar(tReparto & reparto);


void inicializar(tReparto & reparto) {
	reparto.contador = 0;
	for (int i = 0; i < MAX_ACTORES; i++) {
		reparto.actores[i] = " ";
	}
}

istream& operator>>(istream& i, tReparto & reparto) {

	i >> reparto.contador;
	i.ignore('\1');
	for (int j = 0; j < reparto.contador; j++) {
		getline(i, reparto.actores[j]);
	}
	return i;
}

bool aparece(tReparto const& reparto, string actor, int & pos) {
	bool ap = false;
	int sig = pos+1;

	if (pos < reparto.contador) {
		if (actor == reparto.actores[pos]) { ap = true; }
		else { ap = aparece(reparto, actor, sig); }
	}

	return ap;
}