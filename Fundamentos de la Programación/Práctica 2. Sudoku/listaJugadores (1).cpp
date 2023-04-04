#include "listaJugadores.h"
#include <fstream>
#include <iostream>
#include <string>
#include "checkML.h"

using namespace std;

//prototipos
void ordenar(tListaJugadores & lista, string id, int p, int pos);
bool montonLleno(tListaPtr p);
void igualarListas(tListaJugadores & l1, const tListaJugadores l2);

void creaListaVacia(tListaJugadores & lista) {
	lista.jugador = new tJugadorPtr[MAX_JUGADORES];
	lista.cont = 0;
	lista.max = MAX_JUGADORES;
}

bool cargar(tListaJugadores & lista) {
	int i = 0, p;
	ifstream archivo;
	string id = " ";
	bool carga = false;
	archivo.open("listaJugadores.txt");

	creaListaVacia(lista);

	if (!archivo.is_open()) { carga = false;}
	else {
		archivo >> id;
		while (id != " " && i < lista.max) { //PREGUNTAR CENTINELA
			lista.jugador[i] = new tJugador;
			if (!montonLLeno(lista.jugador[i])) {
				igualarId(*lista.jugador[i], id);
				archivo >> p;
				igualarPuntosJug(*lista.jugador[i], p);
				lista.cont++;
				id = " ";
				archivo >> id;
				i++;
				if (i == lista.max) { ampliar(lista); }
			}
		}
		carga = true;
	}
	archivo.close();
	return carga;
}

void mostrar(const tListaJugadores & lista) {
	cout << "LISTA DE JUGADORES" << endl;
	for (int i = 0; i < lista.cont; i++) {
		cout << toString(*lista.jugador[i]) << endl;
		cout << "-----------------" << endl;
	}
}

bool guardar(const tListaJugadores & lista) {  
	ofstream a;
	bool escrito;
	string cad;

	a.open("listaJugadores.txt");
	if (!a.is_open()) { escrito = false;}
	else {
		for (int i = 0; i < lista.cont; i++) {
			cad = toString(*lista.jugador[i]); 
			a << cad << endl;	
		}
		escrito = true;
	}
	a.close();

	return escrito;
}


void puntuarJugador(tListaJugadores & lista, int puntos){
	string id;
	int pos;
	cout << "Escribe tu identificador: ";
	cin >> id;

	if (buscar(lista, id, pos,0, lista.cont-1)) { 
		modificarJugador(*lista.jugador[pos], puntos); 
		cout << "Se han actualizado tus puntos, " << id << "!" << endl;
	}
	else { 
		if (lista.cont == lista.max) { ampliar(lista); }
		else if (lista.cont == 0) { pos = 0; }
		ordenar(lista, id, puntos, pos);
		cout << "Has sido anadido a la lista, " << id << "!" << endl;
		lista.cont++;
	}
}

void ordenar(tListaJugadores & lista, string id, int p, int pos) { 
	lista.jugador[lista.cont] = new tJugador;
	if (!montonLLeno(lista.jugador[lista.cont])) {
		iniciaJugador(*lista.jugador[lista.cont]);
		for (int j = lista.cont; j > pos; j--) {
			intercambiaJugador(*lista.jugador[j], *lista.jugador[j - 1]);
		}
		igualarId(*lista.jugador[pos], id);
		igualarPuntosJug(*lista.jugador[pos], p);
	}
}


// buscar recursiva:
bool buscar(const tListaJugadores & lista, string id, int & pos, int ini, int fin) {
	bool ex;
	
	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (id == devuelveId(*lista.jugador[pos])) { ex = true; }
		else if (id < devuelveId(*lista.jugador[pos])) { ex = buscar(lista, id, pos, ini, pos - 1); }
		else { ex = buscar(lista, id, pos, pos+1, fin);	}
	}
	else {
		ex = false;
		pos = (ini != pos) ? pos + 1 : pos;
	}

	return ex;
}

tListaJugadores ordenarPorRanking(const tListaJugadores & lista) {
	tJugadorPtr tmp = NULL;
	tListaJugadores rank;
	int pos;

	igualarListas(rank, lista);

	for (int i = 1; i < rank.cont; i++) {
		pos = i;
		while ((pos > 0) && (!menor(*rank.jugador[pos], *rank.jugador[pos - 1]))) {
			tmp = rank.jugador[pos - 1];
			rank.jugador[pos - 1] = rank.jugador[pos];
			rank.jugador[pos] = tmp;
			pos--;
		}
	}
	return rank;
}

void ampliar(tListaJugadores & lista) { //comprobar nulles
	tListaPtr aux = NULL;
	lista.max = lista.max * 2;
	aux = new tJugadorPtr[lista.max];
	if (!montonLleno(aux)) {
		for (int i = 0; i < lista.cont; i++) { 
			aux[i] = lista.jugador[i]; 
		}
	}
	borrarListaJugadores(lista);
	lista.jugador = aux;
}

void borrarListaJugadores(tListaJugadores & lista) {
	delete [] lista.jugador;
}

bool montonLleno(tListaPtr p) {
	return p == NULL;
}

void borrarJugadores(tListaJugadores & lista) {
	for (int i = 0; i < lista.cont; i++) {
		eliminarJugadores(lista.jugador[i]);
	}
}

void igualarListas(tListaJugadores & l1, tListaJugadores l2) {
	l1.jugador = new tJugadorPtr[l2.max];
	l1.cont = 0;
	l1.max = l2.max;
	for (int i = 0; i < l2.cont; i++) {
		l1.jugador[i] = new tJugador(*l2.jugador[i]);
		l1.cont++;
	}	
}
