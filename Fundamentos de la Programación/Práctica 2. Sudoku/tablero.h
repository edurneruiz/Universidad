#pragma once

#include <string>
#include "casilla.h"

using namespace std;

typedef tCasilla tTablero[NUM_ELEMENTOS][NUM_ELEMENTOS];

void iniciaTablero(tTablero tablero); //inicia una por una las casillas del tablero
bool cargarTablero(string nombreFichero, tTablero tablero); //carga el tablero desde un archivo, rellenando cada casilla y su conjunto de posibles
void dibujarTablero(const tTablero tablero); //dibuja una por una las casillas del tablero
bool ponerNum(tTablero &tablero, int fila, int col, int c); //dadas las coordenadas de una casilla y un numero, añade ese numero a la casilla si esta vacia y si el num pertenece al posibles. Actualiza los posibles de las casillas a las que afecta
bool borrarNum(tTablero tablero, int fila, int col); // //dadas las coordenadas de una casilla y un numero, borra ese numero si esta rellena. Actualiza los posibles de las casillas 
bool tableroLleno(const tTablero tablero); //devuelve true si todas las casillas estan fijas o rellenas y false en c.c.
void mostrarPosibles(const tTablero tablero, int fila, int col); //muestra el conjunto de posibles de una casilla con las coordenadas dadas
void rellenarSimples(tTablero tablero);//rellena todas las casillas cuyo conjunto de posibles sea uitario y actualiza las casillas afectadas
bool comprobarInterv(int valor);//comprueba que el valor esté entre 0 y 8
bool comprobarNum(int valor);//comprueba que el valor esté entre 1 y 9
