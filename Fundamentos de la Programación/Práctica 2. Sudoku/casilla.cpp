#include <iostream>	
#include "casilla.h"
#include "Windows.h"
#include "checkML.h"

using namespace std;

// prototipos de funciones
void colorFondo(int color); 
int asignarColor(tEstado estado); //asigna un color a cada casilla dependiendo de su estado 


void iniciaCasilla(tCasilla & casilla) {
	casilla.est = vacia; 
	cjto_lleno(casilla.posibles);
}

void rellenaCasilla(tCasilla & casilla, char c, bool fija) {
	casilla.est = (c == ' ') ? vacia : (fija) ? fijada : rellenada;
	if (casilla.est != vacia) {
		casilla.num = c - '0';
	}
	else { casilla.num = 0; }
}

void dibujaCasilla(const tCasilla & casilla) {
	colorFondo(asignarColor(casilla.est));
	if (casilla.est == vacia) { cout << " "; }
	else { cout << casilla.num; }
	colorFondo(0);
}

bool esSimple(const tCasilla & casilla, int & numero) {
	bool simple;
	if (casilla.est == fijada || casilla.est == rellenada) { simple = false; }
	else { simple = esUnitario(casilla.posibles, numero); }
	return simple;
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

int asignarColor(tEstado estado) {
	int color;
	color = (estado == vacia) ? 0 : (estado == fijada) ? 1 : 4;
	return color;
}

tEstado devuelveEst(tCasilla const& casilla) {
	return casilla.est;
}
int devuelveNum(tCasilla const& casilla) {
	return casilla.num;
} 

tConjunto igualarPosibles(tCasilla & casilla, tConjunto pos){
	casilla.posibles = pos;
	return casilla.posibles;
}

tConjunto devuelvePosibles(tCasilla  casilla) {
	return casilla.posibles;
}