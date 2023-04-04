#pragma once
#include "reparto.h"

typedef struct {
	string titulo;
	string director;
	string genero;
	float valoracion;
	tReparto reparto;
} tPelicula;

typedef tPelicula* tPtrPeli;

// prototipos
istream& operator>> (istream& i, tPelicula & pelicula);
bool operator<(tPelicula const& p1, tPelicula const& p2);
bool compararPeliculasGenero(tPelicula const& p1, tPelicula const& p2);
bool interviene(tPelicula const& pelicula, string actor);
void mostrar(tPelicula const& pelicula);