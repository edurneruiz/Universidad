#include "jugador.h"
#include <iostream>
#include "checkML.h"

using namespace std;


void iniciaJugador(tJugador & jugador) {
	jugador.id = " ";
	jugador.puntos = 0;
}

string toString(tJugador & jugador) {
	string cad;
	cad = jugador.id + " " + to_string(jugador.puntos);
	return cad;
}

void modificarJugador(tJugador & jugador, int puntos) {
	jugador.puntos += puntos;
}

bool operator<(const tJugador & opIzq, const tJugador & opDer) {
	return opIzq.id < opDer.id;
}

bool menor(const tJugador & j1, const tJugador & j2) {
	bool menor;
	menor = (j1.puntos < j2.puntos) ? true : ((j1.puntos == j2.puntos) && (j2 < j1)) ? true : false;
	return menor;
}

void igualarId(tJugador & jugador, string id) {
	jugador.id = id;
}

void igualarPuntosJug(tJugador & jugador, int p) {
	jugador.puntos = p;
}

string devuelveId(const tJugador & j) {
	return j.id;
}

int devuelvePuntosJug(const tJugador & j) {
	return j.puntos;
}

void intercambiaJugador(tJugador & j1, tJugador const& j2) {
	j1.id = j2.id;
	j1.puntos = j2.puntos;
}

bool montonLLeno(tJugadorPtr p) {
	if (p == NULL) { cout << "No se dispone de mas memoria!" << endl; }
	return p == NULL;
}

void eliminarJugadores(tJugadorPtr p) {
	delete p;
}