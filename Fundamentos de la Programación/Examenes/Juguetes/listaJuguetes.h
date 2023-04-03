#pragma once
#include "juguete.h"
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct {
	tPtrJuguete lista;
	int cont_50;
	int cont_60;
	int cont_70;
	int cont_80;
} tListaJuguetes;

//prototipos

bool cargar(tListaJuguetes & j);
bool buscar(tListaJuguetes const& j, string id, int & pos, int ini, int fin);
void insertar(tListaJuguetes & j, string id, tDecada decada, long int unidades, float precio);
bool eliminar(tListaJuguetes & j, string id);
void mostrar(tListaJuguetes const& j);
void liberar(tListaJuguetes & j);
long int contadorLista(tListaJuguetes const& j);
tJuguete devolverJuguete(tListaJuguetes const& j, int pos);