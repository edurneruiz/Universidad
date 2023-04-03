#include "coleccion.h"
using namespace std;

//prototipos
void inicializar(tColeccion & c);


void inicializar(tColeccion & c) {
	c.cont = 0;
	for (int i = 0; i < MAX_JUGUETES; i++) { c.lista[i] = NULL; }
}


tColeccion crearColeccion(tListaJuguetes & j, float precio_max, tDecada decada) {
	int i = 0;
	float suma = 0;
	tJuguete juguete;
	tColeccion c;
	inicializar(c);

	while ((i < contadorLista(j)) && (suma < precio_max)) {
		juguete = devolverJuguete(j, i);
		if ((decada == devolverDecada(juguete)) && (devolverUnidades(juguete) != 0)) {
			c.lista[c.cont] = new tJuguete;
			añadirJuguete(*c.lista[c.cont], devolverId(juguete), decada, 1, devolverPrecio(juguete));
			suma += devolverPrecio(juguete);
			eliminar(j, devolverId(juguete));
			c.cont++;
		}
		i++;
	}

	return c;
}


void mostrar(tColeccion & coleccion, int pos) {
	int sig = pos + 1;
	if (pos != coleccion.cont) {
		mostrarJuguete(*coleccion.lista[pos]);
		mostrar(coleccion, sig);
	}
}

void borrar(tColeccion & c) {
	for (int i = 0; i < c.cont; i++) {
		delete c.lista[i];
	}
}
