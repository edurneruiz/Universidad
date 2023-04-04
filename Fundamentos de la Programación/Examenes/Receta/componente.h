#pragma once
#include "listaIngredientes.h"

typedef struct {
	tPtrIngrediente ing;
	float gramos;
} tComponente;

typedef tComponente* tPtrComponente;

//prototipos
tComponente leeComponente(tListaIngredientes & i);
void muestra(tComponente const& comp);
tPtrIngrediente devolverIngrediente(tComponente const& comp);
float calcularCalorias(tComponente const& comp);
void igualarComponentes(tComponente & c1, tComponente const& c2);
float devolverGramos(tComponente const& comp);
bool mismoComponente(tComponente const& c1, tComponente const& c2);
void actualizarGramos(tComponente & comp, float gram);