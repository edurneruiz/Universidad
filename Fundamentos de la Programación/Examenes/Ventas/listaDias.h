#pragma once
#include "listaVentas.h"

const int MAX_DIAS = 200;

typedef struct {
	string fecha;
	tListaVentas ventas;
} tDia;

typedef tDia* tLista[MAX_DIAS];

typedef struct {
	tLista lista;
	int cont;
} tListaDias;

//prototipos
bool encuentra(tListaDias const& d, string fecha, int & pos, int ini, int fin);
float totalVentas(tListaDias const& d);
void insertaDia(tListaDias & d, string fecha, tVenta & venta);
bool carga(tListaDias & d);
void muestra(tListaDias const& d);
void destruye(tListaDias & d);
