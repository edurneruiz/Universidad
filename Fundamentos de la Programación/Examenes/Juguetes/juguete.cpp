#include "juguete.h"
#include <iomanip>
#include <iostream>
#include <string>

//prototipos funciones
string cadDecada(tDecada decada);



float precioVenta(tJuguete const& juguete) {
	float precio;
	precio = (juguete.decada == a�os50) ? juguete.precio*1.20 : (juguete.decada == a�os60) ? juguete.precio*1.15 : (juguete.decada == a�os70) ? juguete.precio*1.1 : juguete.precio*1.05;
	return precio;
}
void mostrarJuguete(tJuguete & juguete) {
	cout << left << setw(20) << juguete.id << setw(10) << cadDecada(juguete.decada) << setw(4) << juguete.unidades << setw(10) << " uds." <<  setw(5) << setprecision(2) << precioVenta(juguete) << setw(15) << " eur." << setprecision(2) << juguete.precio << " eur." << endl;
}

string devolverId(tJuguete const& juguete) {
	return juguete.id;
}

tDecada escDecada(int dec) {
	tDecada d;
	d = (dec == 50) ? a�os50 : (dec == 60) ? a�os60 : (dec == 70) ? a�os70 : a�os80;
	return d;
}

string cadDecada(tDecada decada) {
	string d;
	d = (decada == a�os50) ? "a�os 50" : (decada == a�os60) ? "a�os 60" : (decada == a�os70) ? "a�os 70" : "a�os 80";
	return d;
}

tDecada devolverDecada(tJuguete const& juguete) {
	return juguete.decada;
}

void sumarUnidades(tJuguete & juguete, long int unidades) {
	juguete.unidades += unidades;
}

void restarUnidades(tJuguete & juguete) {
	juguete.unidades--;
}

long int devolverUnidades(tJuguete const& juguete) {
	return juguete.unidades;
}

void a�adirJuguete(tJuguete & j, string id, tDecada decada, long int unidades, float precio) {
	j.id = id;
	j.decada = decada;
	j.unidades = unidades;
	j.precio = precio;
}

float devolverPrecio(tJuguete const& juguete) {
	return juguete.precio;
}