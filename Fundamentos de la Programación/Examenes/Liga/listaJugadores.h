#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_JUGADORES = 10;

typedef struct {
	string nombre;
	int num;
	int goles;
	float precio;
} tJugador;

typedef tJugador* tJugadorPtr;
typedef tJugadorPtr tLista[MAX_JUGADORES];

typedef struct {
	tLista lista;
	int cont;
} tListaJugadores;

//prototipos
void cargar(tListaJugadores & j, ifstream& archivo);
void insertar(tListaJugadores & j, tJugador & jug);
void eliminar(tListaJugadores & j, int pos);
void liberar(tListaJugadores & j);
void mostrar(tListaJugadores const& j);
float devolverPrecio(tJugador const& jug);
bool jugadorMasCaro(float dinero, tListaJugadores const& plantilla, int pos);
float venderJugador(tListaJugadores & comp, tListaJugadores & vend, int pos);