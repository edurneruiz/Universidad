#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_INGREDIENTES = 50;

typedef struct {
	string nombre;
	float calorias;
} tIngrediente;

typedef tIngrediente* tPtrIngrediente;

typedef tPtrIngrediente tListaIng[MAX_INGREDIENTES];

typedef struct {
	tListaIng lista;
	int cont;
} tListaIngredientes;

//prototipos
void insertar(tListaIngredientes & i, tIngrediente const& ing);
bool carga(tListaIngredientes & i);
string selectIngred(tListaIngredientes const& i);
int buscarPos(tListaIngredientes const& i, string nombre, int & pos, int ini, int fin);
int devolverContador(tListaIngredientes const& i);
string devolverNombre(tIngrediente const& ing);
float devolverCalorias(tIngrediente const& ing);
void igualarIngredientes(tPtrIngrediente & ing, tListaIngredientes const&i, int pos);
void eliminar(tListaIngredientes & i);
