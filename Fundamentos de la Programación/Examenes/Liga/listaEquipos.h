#pragma once
#include "listaJugadores.h"

const int MAX_EQUIPOS = 20;

typedef struct {
	string nombre;
	float dinero;
	int puntos;
	tListaJugadores plantilla;
} tEquipo;

typedef tEquipo* tListaEquipos;

//prototipos
bool cargar(tListaEquipos & eq, int & num);
int buscar(tListaEquipos const& e, string equipo);
void mostrar(tEquipo const& e);
void mostrarDinero(tEquipo const& e);
int elegir(tEquipo & eq);
void liberar(tListaEquipos & e, int num);
bool dineroSuficiente(tEquipo const& comp, tEquipo const& vend, int pos);
void traspasar(tEquipo & comp, tEquipo & vend, int pos);

