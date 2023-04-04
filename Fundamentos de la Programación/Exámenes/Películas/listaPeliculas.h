#pragma once
#include "pelicula.h"

const int MAX_PELICULAS = 50;

typedef tPtrPeli tListaPeliculas[MAX_PELICULAS];

typedef struct {
	tListaPeliculas lista;
	int cont;
} tPeliculasTotal;

//prototipos
bool cargar(tPeliculasTotal & p);
tPeliculasTotal filtrarPorActor(tPeliculasTotal const& p, string actor);
void mostrar(tPeliculasTotal const& p);
tPeliculasTotal ordenarPorGenero(tPeliculasTotal & p);
tPeliculasTotal ordenarPorValoracion(tPeliculasTotal & p);
void destruir(tPeliculasTotal & p);