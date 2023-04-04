#include "liga.h"
#include <ctime>


void inicializarLiga(tLiga & liga, tListaEquipos const& eq, int num) {
	liga.cont = num;
	liga.equipos = eq;
}


void transferir(int pos, tEquipo & comprador, tEquipo & vendedor) {
	if (dineroSuficiente(comprador, vendedor, pos)) {
		traspasar(comprador, vendedor, pos);
	}
	else { cout << "no hay suficiente dinero" << endl; }
}

void mostrar(tLiga const& liga) {
	for (int i = 0; i < liga.cont; i++) {
		mostrar(liga.equipos[i]);
	}
	cout << endl;
}

/*void jugarPartido(tLiga & liga) {
	int pos1, pos2;

}*/

void mostrarDinero(tLiga const& liga) {
	for (int i = 0; i < liga.cont; i++) {
		mostrarDinero(liga.equipos[i]);
	}
}

tEquipo devolverEquipo(tLiga const& liga, int pos) {
	return liga.equipos[pos];
}

int buscar(tLiga const& liga, string equipo) {
	int pos = buscar(liga.equipos, equipo);
	return pos;
}

void liberar(tLiga & liga) {
	liberar(liga.equipos, liga.cont);
}