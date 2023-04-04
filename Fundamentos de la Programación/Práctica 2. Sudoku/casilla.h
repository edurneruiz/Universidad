#pragma once
#include "conjunto.h"

typedef enum {vacia, fijada, rellenada} tEstado;

typedef struct {
	tEstado est;
	int num;
	tConjunto posibles;
} tCasilla;

void iniciaCasilla(tCasilla & casilla); // inicia la casilla a vacia y llena el cjto de posibles 
void rellenaCasilla(tCasilla & casilla, char c, bool fija = false); // rellena el estado y el nº de casilla de acuerdo con los valores de fija (true=fija, false=rellena) y c
void dibujaCasilla(const tCasilla & casilla); //asigna el color de la casilla segun el estado y muestra el numero correspondiente
bool esSimple(const tCasilla & casilla, int & numero); //devuelve true y un valor si su conjunto posibles es unitario y esta vacia y false si esta fija o rellenada

tEstado devuelveEst(tCasilla const& casilla); //devuelve el estado de la casilla
int devuelveNum(tCasilla const& casilla); //devuelve el numero de la casila
tConjunto igualarPosibles(tCasilla & casilla, tConjunto pos); //iguala el conjunto posibles de la casilla al conjunto dado 
tConjunto devuelvePosibles(tCasilla casilla); // devuelve el conjunto posibles de la casilla