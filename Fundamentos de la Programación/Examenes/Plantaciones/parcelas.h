#pragma once
#include "plantacion.h"
using namespace std;

const int tam_max = 1000;

typedef struct {
	string id;
	int fila;
	int columna;
	int platanos;
} tParcela;

typedef tParcela* tListaParcelas[tam_max];

typedef struct {
	tListaParcelas lista;
	int cont;
} tParcelasTotal;

//prototipos

bool operator< (const tParcela p1, const tParcela p2);
ostream& operator<< (ostream& o, const tParcela p);
tParcelasTotal crearParcelas(tPlantacion const& plantacion, int lado);
void mostrarListaParcelas(tParcelasTotal const& parcelas, int pos); 
tParcelasTotal mezclar(tParcelasTotal const& p1, tParcelasTotal const& p2);
void liberar(tParcelasTotal & parcelas);
string coordenadas(int x, int y);

int devolverPlatanos(tParcelasTotal const& p, int num);
tParcela* devolverParcela(tParcelasTotal const& p, int num);
int devolverContador(tParcelasTotal const& p);