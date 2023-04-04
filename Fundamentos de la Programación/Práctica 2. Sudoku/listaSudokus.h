#pragma once

#include "juego.h"

const int MAX_SUDOKUS = 20;

typedef tSudoku tLista[MAX_SUDOKUS];

typedef struct {
	tLista lista;
	int contador;
} tListaSudokus;

void creaListaVacia(tListaSudokus & lista); //inicializa una lista dada
bool cargar(tListaSudokus & lista); // devuelve true si consigue cargar la lista desde archivo o false en caso contrario
void mostrar(const tListaSudokus & lista); // muestra la lista de sudokus
tSudoku cargar(tListaSudokus lista, int i); // devuelve el sudoku elegido por el usuario

//v2
bool guardar(const tListaSudokus & lista); //devuelve true si consigue guardar la lista en archivo o false en caso contrario
bool buscarFichero(const tListaSudokus & lista, string a); //devuelve true si el sudoku se encuentra en la lista o false en caso contrario
int buscarPos(const tListaSudokus & lista, const tSudoku & sudoku); //determina la posicion en la cual debería introducirse el sudoku dado
bool registrarSudoku(tListaSudokus & lista); //devuelve true si consigue añadir el sudoku o false en caso contrario