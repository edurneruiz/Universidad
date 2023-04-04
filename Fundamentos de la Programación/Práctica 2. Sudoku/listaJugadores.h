#pragma once

#include "jugador.h"

const int MAX_JUGADORES = 5;
typedef tJugadorPtr* tListaPtr;
typedef struct {
	tListaPtr jugador;
	int cont;
	int max;
}tListaJugadores;


void creaListaVacia(tListaJugadores & lista); // inicializa lista a una lista vacía.
bool cargar(tListaJugadores & lista); // guarda en lista el contenido del archivo listaJugadores.txt; devuelve un booleano que indica si la carga se ha podido realizar.
void mostrar(const tListaJugadores & lista); //visualiza por pantalla la lista de jugadores dada.
bool guardar(const tListaJugadores & lista); /* almacena en el archivo listaJugadores.txt el contenido de lista y devuelve un valor booleano indicando si la acción fue posible*/
void puntuarJugador(tListaJugadores & lista, int puntos); 
bool buscar(const tListaJugadores & lista, string id, int & pos, int ini, int fin); 
tListaJugadores ordenarPorRanking(const tListaJugadores & lista); 

//v3
void ampliar(tListaJugadores & lista); //amplía la dimensión del array dinámico de lista al doble de la que tiene.
void borrarListaJugadores(tListaJugadores & lista); //libera la memoria dinámica usada por lista.
void borrarJugadores(tListaJugadores & lista); //borra cada jugador de la memoria dinámica