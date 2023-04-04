#pragma once
#include "venta.h"
#include <fstream>

const int MAX_VENTAS = 30;

typedef struct {
	tVentaPtr lista;
	int cont;
} tListaVentas;

//prototipos
void inicializar(tListaVentas & v);
void insertaVenta(tListaVentas & v, tVenta & venta);
void muestra(tListaVentas const& v);
float totalVentas(tListaVentas const& v);
void destruye(tListaVentas const& v);
