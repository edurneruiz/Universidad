#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

typedef struct {
	string hora;
	long int codigo;
	float precio;
	int unidades;
} tVenta;

typedef tVenta* tVentaPtr;

//prototipos

void muestra(tVenta const& venta);
float totalVenta(tVenta const& venta);
bool operator==(tVenta const& v1, tVenta const& v2);
bool operator<(tVenta const& v1, tVenta const& v2);
istream& operator >>(istream& i, tVenta & venta);