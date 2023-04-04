#pragma once
#include "parcelas.h"
#include "plantacion.h"

const int MAX_CUADRILLAS = 20;

typedef struct {
	string id;
	int max_p;
	tParcela* p;
} tCuadrilla;

typedef tCuadrilla* tListaCuadrillas;

typedef struct {
	tListaCuadrillas lista;
	int cont;
} tCuadrillasTotal;

//prototipos

bool operator<(tCuadrilla const& c1, tCuadrilla const& c2);
ostream& operator<<(ostream& o, tCuadrilla const& c);
istream& operator>>(istream& i, tCuadrilla & c);
void inicializarListaCuadrillas(tCuadrillasTotal & cuadrillas);
tCuadrillasTotal crearListaCuadrillas();
void asignarParcelas(tParcelasTotal const& parcelas, tCuadrillasTotal & cuadrillas);
void mostrarAsignaciones(tCuadrillasTotal const& cuadrillas);
void liberar(tCuadrillasTotal & cuadrillas);
bool escribirCuadrillas(tCuadrillasTotal const& cuadrillas);