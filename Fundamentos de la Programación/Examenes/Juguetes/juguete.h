#pragma once
#include <iostream>
using namespace std;

typedef enum {años50, años60, años70, años80} tDecada;

typedef struct {
	string id;
	tDecada decada;
	long int unidades;
	float precio;
} tJuguete;

typedef tJuguete* tPtrJuguete;

//prototipos de funciones

float precioVenta(tJuguete const& juguete);
void mostrarJuguete(tJuguete & juguete);
string devolverId(tJuguete const& juguete);
tDecada escDecada(int dec);
tDecada devolverDecada(tJuguete const& juguete);
float devolverPrecio(tJuguete const& juguete);
long int devolverUnidades(tJuguete const& juguete);
void sumarUnidades(tJuguete & juguete, long int unidades);
void restarUnidades(tJuguete & juguete);
void añadirJuguete(tJuguete & j, string id, tDecada decada, long int unidades, float precio);

