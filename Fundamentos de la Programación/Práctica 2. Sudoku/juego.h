#pragma once

#include "tablero.h"
#include <string>

using namespace std;

typedef struct {
	int puntos;
	string archivo;
}tSudoku;

typedef struct {
	tSudoku sudoku;
	tTablero tablero;
	bool relleno;
}tJuego;

void iniciaJuego(tJuego & juego, const tSudoku & sudoku); 
void mostrarJuego(const tJuego & juego); //muestra la informacion del sudoku asi como el tablero
bool cargaJuego(tJuego & juego, const tSudoku & sudoku); // actualiza el tablero de juego con el contenido del archivo del Sudoku recibido.
int jugarUnSudoku(const tSudoku & sudoku); // ejecuta la opcion elegida en el menú 
void iniciaSudoku(tSudoku & sudoku); // inicializa el sudoku a 0
void igualarArchivo(tSudoku & sudoku, string arch); // iguala el archivo del sudoku al archivo dado
void igualarPuntos(tSudoku & sudoku, int p); // iguala los puntos del sudoku al valor dado
void mostrarSudoku(tSudoku const& sudoku); // muestra los datos del sudoku dado
bool operator <(tSudoku sudoku1,tSudoku sudoku2);
string devuelveArchivo(tSudoku const& sudoku);//devuelve el archivo del sudoku dado
void intercambiaSudoku(tSudoku & s1, tSudoku const& s2);//asigna a s1 el archivo y los puntos de s2
int devuelvePuntos(tSudoku const& sudoku); //devuelve los puntos del sudoku dado