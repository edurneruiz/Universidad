#pragma once

const int NUM_ELEMENTOS = 9;

typedef struct {
	bool elementos[NUM_ELEMENTOS];
	int numElem;
}tConjunto;


void cjto_vacio(tConjunto & conjunto); // vacia el conjunto dado
void cjto_lleno(tConjunto & conjunto); // llena el conjunto dado
int numElems(const tConjunto & conjunto); // devuelve el numero de elementos (true) del conjunto dado
bool pertenece(const tConjunto & conjunto, int valor); // determina si el valor dado pertenece al conjunto dado
void addElemento(tConjunto & conjunto, int valor); // añade (pone a true) al conjunto dado el valor dado si no pertenece
void delElemento(tConjunto & conjunto, int valor); // elimina (pone a false) el valor dado del conjunto dado si pertenece
bool esUnitario(const tConjunto & conjunto, int & elemento); // devuelve true si el conjunto tiene un elemento (solo un true) o false en c.c
void mostrar(const tConjunto & conjunto); //muestra los valores que pertenecen al cjto
