#pragma once
#include "componente.h"

const int MAX_COMP = 20;

typedef tPtrComponente tLista;

typedef struct {
	string nombre;
	tLista lista;
	int cont;
} tReceta;

//prototipos

tReceta crear();
bool insertar(tReceta & r, tComponente const& comp);
void muestra(tReceta const& r);
void eliminar(tReceta & r);