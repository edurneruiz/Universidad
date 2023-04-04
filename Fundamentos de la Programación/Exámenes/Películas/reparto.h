#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ACTORES = 10;

typedef string tActores[MAX_ACTORES];

typedef struct {
	tActores actores;
	int contador;
} tReparto;

//prototipos 
istream& operator>>(istream& i, tReparto & reparto);
bool aparece(tReparto const& reparto, string actor, int & pos);
