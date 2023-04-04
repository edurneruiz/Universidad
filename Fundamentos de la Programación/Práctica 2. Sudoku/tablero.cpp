#include "tablero.h"
#include <fstream>
#include <iostream>
#include <string>
#include "checkML.h"

using namespace std;

//prototipos

void rellenaPosibles(tTablero  tablero, int filas, int columnas); //dadas las coordenadas de una casilla, llena el cjto de posibles y recorre su fila columna y cuadrante eliminando del cjto los números que se encuentren
void posiblesCasilla(tTablero tablero); //rellena uno por uno los cjto posibles de cada casilla del tablero
void eliminaPosibles(tTablero  tablero, int filas, int columnas); //dadas las coordenadas rellena, recorre su fila, columna y cuadrante eliminando su numero de los conj posibles de las casillas 


void iniciaTablero(tTablero tablero) {
	for (int filas = 0; filas < NUM_ELEMENTOS; filas++) {
		for (int columnas = 0; columnas < NUM_ELEMENTOS; columnas++) {
			iniciaCasilla(tablero[filas][columnas]);
		}
	}
}

bool cargarTablero(string nombreFichero, tTablero tablero) {
	bool carga;
	char c;
	ifstream archivo;
	archivo.open(nombreFichero);
	if (!archivo.is_open()) { carga = false; }
	else {
		for (int filas = 0; filas < NUM_ELEMENTOS; filas++) {
			for (int columnas = 0; columnas < NUM_ELEMENTOS; columnas++) {
				archivo.get(c);
				if (c == '\n') {
					archivo.get(c);
				}
				rellenaCasilla(tablero[filas][columnas], c, true);
			}
		}
		posiblesCasilla(tablero);
		carga = true;
	}
	archivo.close();
	return carga;
}



void dibujarTablero(const tTablero tablero) {
	cout << " 0 1 2  3 4 5  6 7 8" << endl;
	for (int filas = 0; filas < NUM_ELEMENTOS; filas++) {
		if (filas % 3 == 0) {
			cout <<"**********************";
			cout << endl;
		}
		for (int columnas = 0; columnas < NUM_ELEMENTOS; columnas++) {
			if (columnas % 3 == 0) { cout << "|"; }
			dibujaCasilla(tablero[filas][columnas]);
			cout << " ";
		}
		cout << "|" << filas << endl;
	}
	cout << "**********************";
	cout << endl;
}

void rellenaPosibles(tTablero  tablero, int filas, int columnas) {
	int fils = (3 * (filas / 3)); //para recorrer por cuadrantes 3x3
	int cols = (3 * (columnas / 3));
	tConjunto pos;
	cjto_lleno(pos);

	for (int col = 0; col < NUM_ELEMENTOS; col++) { //fila de esa casilla
			delElemento(pos, devuelveNum(tablero[filas][col]));
	}
	for (int fil = 0; fil < NUM_ELEMENTOS; fil++) { //columna de esa casilla
			delElemento(pos, devuelveNum(tablero[fil][columnas]));
	}

	for (int fil = fils; fil < fils + 3; fil++) { //cuadrantes 3x3
		for (int col = cols; col < cols + 3; col++) {
			delElemento(pos, devuelveNum(tablero[fil][col]));
		}
	}
	igualarPosibles(tablero[filas][columnas], pos); //iguala el posibles de la casilla dada al conjunto con el que se opera
}

void posiblesCasilla(tTablero tablero) {
	for (int filas = 0; filas < NUM_ELEMENTOS; filas++) {
		for (int columnas = 0; columnas < NUM_ELEMENTOS; columnas++) {
			rellenaPosibles(tablero, filas, columnas);
		}
	}
}

bool ponerNum(tTablero& tablero, int fila, int col, int c) {
	bool si = false;
	tConjunto pos = devuelvePosibles(tablero[fila][col]);

	if (comprobarNum(c) && comprobarInterv(fila) && comprobarInterv(col) && devuelveEst(tablero[fila][col]) == vacia && pertenece(pos, c)) {
		rellenaCasilla(tablero[fila][col], c +'0', false);
		delElemento(pos = devuelvePosibles(tablero[fila][col]), c);
		si = true;
		eliminaPosibles(tablero, fila, col);
	}
	else if (!pertenece(pos, c)) { cout << "EL "<< c << " NO SE PUEDE PONER EN LA CASILLA ("<< fila << "," << col << ")!!" << endl; }
	else { cout << "LA CASILLA ("<< fila << "," << col << ") NO ESTA VACIA!" << endl; }

	return si;
}

void eliminaPosibles(tTablero  tablero, int filas, int columnas) {
	int fils = (3 * (filas / 3)); //para recorrer por cuadrantes 3x3
	int cols = (3 * (columnas / 3));
	tConjunto pos;

	for (int col = 0; col < NUM_ELEMENTOS; col++) { //casillas de esa fila
		delElemento(pos = devuelvePosibles(tablero[filas][col]), devuelveNum(tablero[filas][columnas]));
		pos = igualarPosibles(tablero[filas][col], pos);
	}
	for (int fil = 0; fil < NUM_ELEMENTOS; fil++) { //casillas de esa columna
		delElemento(pos = devuelvePosibles(tablero[fil][columnas]), devuelveNum(tablero[filas][columnas]));
		pos = igualarPosibles(tablero[fil][columnas], pos);
	}

	for (int fil = fils; fil < fils + 3; fil++) { //casillas de ese cuadrante 3x3
		for (int col = cols; col < cols + 3; col++) {
			delElemento(pos = devuelvePosibles(tablero[fil][col]), devuelveNum(tablero[filas][columnas]));
			pos = igualarPosibles(tablero[fil][col], pos);
		}
	}
}

bool borrarNum(tTablero tablero, int fila, int col) {
	bool hecho = false;
	tConjunto pos;

	if (comprobarInterv(fila) && comprobarInterv(col) && devuelveEst(tablero[fila][col]) == rellenada) {
		addElemento(pos = devuelvePosibles(tablero[fila][col]), devuelveNum(tablero[fila][col]));
		rellenaCasilla(tablero[fila][col], ' ', false);
		posiblesCasilla(tablero); 
	}

	return hecho;
}

bool comprobarInterv(int valor) {
	return (valor >= 0 && valor < NUM_ELEMENTOS);
}

bool comprobarNum(int valor) {
	return (valor > 0 && valor <= NUM_ELEMENTOS);
}

bool tableroLleno(const tTablero tablero) {
	bool lleno = true;
	int f = 0, c;

	while (lleno && f < NUM_ELEMENTOS) {
		c = 0;
		while (lleno && c < NUM_ELEMENTOS) {
			lleno = (!(devuelveEst(tablero[f][c]) == vacia));
			c++;
		}
		f++;
	}
	return lleno;
}

void mostrarPosibles(const tTablero tablero, int fila, int col) {
	mostrar(devuelvePosibles(tablero[fila][col]));
}

void rellenarSimples(tTablero tablero) {
	int elem;
	for (int f = 0; f < NUM_ELEMENTOS; f++) {
		for (int c = 0; c < NUM_ELEMENTOS; c++) {
			if ((devuelveEst(tablero[f][c]) == vacia) && esUnitario(devuelvePosibles(tablero[f][c]), elem)) {
				rellenaCasilla(tablero[f][c], elem + '0', false);
				eliminaPosibles(tablero, f, c);
			}
		}
	}
}


