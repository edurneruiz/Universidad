#pragma once
#include "listaJuguetes.h"
using namespace std;

const int MAX_JUGUETES = 50;

typedef tPtrJuguete tLista[MAX_JUGUETES];

typedef struct {
	tLista lista;
	int cont;
} tColeccion;

//prototipos
tColeccion crearColeccion(tListaJuguetes & j, float precio_max, tDecada decada);
void mostrar(tColeccion & coleccion, int pos); // recursiva
void borrar(tColeccion & c);
