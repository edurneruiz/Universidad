#pragma once
#include "listaEquipos.h"


typedef struct {
	tListaEquipos equipos;
	int cont;
} tLiga;

//prototipos
void inicializarLiga(tLiga & liga, tListaEquipos const& eq, int num);
void transferir(int pos, tEquipo & comprador, tEquipo & vendedor);
void mostrar(tLiga const& liga);
void mostrarDinero(tLiga const& liga); 
tEquipo devolverEquipo(tLiga const& liga, int pos);
int buscar(tLiga const& liga, string equipo);
void liberar(tLiga & liga);
/*void jugarPartido(tLiga & liga);*/