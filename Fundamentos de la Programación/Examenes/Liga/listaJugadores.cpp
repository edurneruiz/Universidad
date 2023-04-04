#include "listaJugadores.h"

//prototipos
void desplazar(tListaJugadores & j, int pos);


void cargar(tListaJugadores & j, ifstream& archivo) {
	archivo >> j.cont;
	for (int i = 0; i < j.cont; i++) {
		j.lista[i] = new tJugador;
		archivo >> j.lista[i]->num;
		archivo.ignore('\1');
		getline(archivo, j.lista[i]->nombre);
		archivo >> j.lista[i]->goles;
		archivo.ignore('\1');
		archivo >> j.lista[i]->precio;
	}
}

void insertar(tListaJugadores & j, tJugador & jug) {
	j.lista[j.cont] = &jug;
	j.cont++;
}
void eliminar(tListaJugadores & j, int pos) {
	for (int i = pos; i < j.cont; i++) {
		j.lista[i] = j.lista[i+1];
	}
	j.cont--;
}
void liberar(tListaJugadores & j) {
	for (int i = 0; i < j.cont; i++) {
		delete j.lista[i];
	}
}

void mostrar(tListaJugadores const& j) {
	for (int i = 0; i < j.cont; i++) {
		cout << "     " << i << ": [Numero " << j.lista[i]->num << "] ";
		cout << "     " << j.lista[i]->nombre << ", ";
		cout << j.lista[i]->goles << " goles, ";
		cout << j.lista[i]->precio << " euros" << endl;
	}
}

float devolverPrecio(tJugador const& jug) {
	return jug.precio;
}

bool jugadorMasCaro(float dinero, tListaJugadores const& plantilla, int pos) {
	return dinero < plantilla.lista[pos]->precio;
}

float venderJugador(tListaJugadores & comp, tListaJugadores & vend, int pos) {
	float ganancia = comp.lista[pos]->precio;
	insertar(comp, *vend.lista[pos]);
	eliminar(vend, pos);
	return ganancia;
}