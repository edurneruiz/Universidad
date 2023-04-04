#pragma once

#include "listaSudokus.h"

typedef struct {
	string id;
	int puntos;
} tJugador;

typedef tJugador* tJugadorPtr;

string toString(tJugador & jugador); /*devuelve la información del jugador dado en un formato de cadena*/
void modificarJugador(tJugador & jugador, int puntos); //añade puntos puntos a los puntos que lleva conseguidos el jugador dado.
bool operator<(const tJugador & opIzq, const tJugador & opDer); //sobrecarga del operador < para datos del tipo tJugador(se compara en base al identificador).
bool menor(const tJugador & j1, const tJugador & j2); /*devuelve true si el jugador j1 tiene menos puntos que el jugador j2, o si tienen los mismos puntos, pero el identificador del jugador j2 es menor que el del jugador j1; false en caso contrario.*/
void iniciaJugador(tJugador & jugador);
void igualarId(tJugador & jugador, string id);//iguala el id dado al id del jugador
void igualarPuntosJug(tJugador & jugador, int p); // igual los puntos recibidos a los puntos del jugador
string devuelveId(const tJugador & j);//devuelve el id del jugador dado
int devuelvePuntosJug(const tJugador & j); //devuelve los puntos del jugador dado
void intercambiaJugador(tJugador & j1, tJugador const& j2); //cambia los datos del j1 para poner los del j2
bool montonLLeno(tJugadorPtr p); // devuelve true si el puntero dado es NULL
void eliminarJugadores(tJugadorPtr p);