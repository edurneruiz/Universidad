#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 100;
typedef int tArboles[MAX][MAX];

typedef struct {
	string id;
	tArboles arboles;
	int num_f;
	int num_col;
} tPlantacion;

//prototipos de funciones

bool cargarPlantacion(tPlantacion & plantacion, string f); 
int calcularPlatanosParcela(tPlantacion const& plantacion, int fila, int col, int lado);
string devolverId(tPlantacion const& plantacion);
int devolverFilas(tPlantacion const& plantacion);
int devolverColumnas(tPlantacion const& plantacion);
