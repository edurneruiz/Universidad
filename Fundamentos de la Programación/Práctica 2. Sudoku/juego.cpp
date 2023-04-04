#include "juego.h"
#include <iostream>
#include "checkML.h"

using namespace std;

//Prototipos

int menu2(); // muestra las diferentes opciones de "jugar"
void pedirCoor(int &f, int&c);//pide la casilla que se quiere modificar comprobando que son valores validos
int pedirNum();//pide y comprueba el numero que se quiere poner en la casilla
void caso4(tTablero tablero); //borra una a una las casillas rellenas del tablero

void iniciaJuego(tJuego & juego, const tSudoku & sudoku) {
	juego.sudoku = sudoku;
	juego.relleno = false;
	iniciaTablero(juego.tablero);
}

void mostrarJuego(const tJuego & juego) {
	cout << "Puntos: " << juego.sudoku.puntos << endl;
	dibujarTablero(juego.tablero);
}

bool cargaJuego(tJuego & juego, const tSudoku & sudoku) {
	return cargarTablero(sudoku.archivo, juego.tablero);
}

int jugarUnSudoku(const tSudoku & sudoku) {
	int op, puntos = -1, c, f, n;
	tJuego juego;
	
	iniciaJuego(juego, sudoku);

	if (!cargaJuego(juego, sudoku)) { cout << "No se ha podido cargar el sudoku!" << endl; }
	else {
		cout << endl;
		mostrarJuego(juego);
		op = menu2();

		while (op != 0) {
			switch (op) {
			case 1: {
				pedirCoor(f, c);
				cout << "Los valores posibles son: {";
				mostrarPosibles(juego.tablero, f, c);
				cout << "}" << endl;
			}
			break;
			case 2: {
				pedirCoor(f, c);
				n = pedirNum();
				ponerNum(juego.tablero, f, c, n);
			}
			break;
			case 3: {
				pedirCoor(f, c);
				borrarNum(juego.tablero, f, c);
			}
			break;
			case 4: { caso4(juego.tablero);	}
			break;
			case 5: { rellenarSimples(juego.tablero); }
			break;
			default: {	cout << "Opcion no valida" << endl;	}
			}
			dibujarTablero(juego.tablero);
			cout << endl;
			juego.relleno = tableroLleno(juego.tablero);
			op = (juego.relleno) ? 0 : menu2();
		}
		puntos = (juego.relleno) ? sudoku.puntos : 0;
	}
	return puntos;
}

int menu2() {
	int op;
	cout << "QUE QUIERES HACER?" << endl;
	cout << "1.- Ver posibles valores de una casilla vacia" << endl;
	cout << "2.- Colocar valor en una casilla" << endl;	
	cout << "3.- Borrar valor de una casilla" << endl;
	cout << "4.- Reiniciar el tablero" << endl;
	cout << "5.- Autocompletar celdas simples" << endl;
	cout << "0.- Abortar la resolucion y volver al menu principal" << endl;
	cout << "Opcion: ";
	cin >> op;
	cout << endl;
	return op;
}

void iniciaSudoku(tSudoku & sudoku) {
	sudoku.archivo = " ";
	sudoku.puntos = 0;
}

void igualarArchivo(tSudoku & sudoku, string arch) {
	sudoku.archivo = arch;
}

string devuelveArchivo(tSudoku const& sudoku) {
	return sudoku.archivo;
}

void intercambiaSudoku(tSudoku & s1, tSudoku const& s2) {
	s1.archivo = s2.archivo;
	s1.puntos = s2.puntos;
}

void igualarPuntos(tSudoku & sudoku, int p) {
	sudoku.puntos=p;
}

int devuelvePuntos(tSudoku const& sudoku) {
	return sudoku.puntos;
}

void mostrarSudoku(tSudoku const& sudoku) {
	cout << "Archivo: " << sudoku.archivo << endl;
	cout << "Puntos: " << sudoku.puntos << endl;
}

void pedirCoor(int &f, int&c) {
	f = -1;
	c = -1;
	while (!comprobarInterv(f)) {
		cout << "Introduce la fila: ";
		cin >> f;
		if (!comprobarInterv(f)) { cout << "No valido! Debe de estar en el intervalo [0, 8]." << endl; }
		else {
			while (!comprobarInterv(c)) {
				cout << "Introduce la columna: ";
				cin >> c;
				if (!comprobarInterv(c)) { cout << "No valido! Debe de estar en el intervalo [0, 8]." << endl; }
			}
		}
	}
}

int pedirNum() {
	int n = 0;
	while (!comprobarNum(n)) {
		cout << "Introduce el numero deseado: ";
		cin >> n;
		if (!comprobarNum(n)) { cout << "No valido! Debe de estar en el intervalo [1, 9]." << endl; }
	}
	return n;
}

void caso4(tTablero  tablero) {
	for (int i = 0; i < NUM_ELEMENTOS; i++) {
		for (int j = 0; j < NUM_ELEMENTOS; j++) {
			borrarNum(tablero, i, j);
		}
	}
}

bool operator <(tSudoku sudoku1, tSudoku sudoku2) {
	bool menor = false;

	if (sudoku1.puntos < sudoku2.puntos) { menor = true; }
	else if (sudoku1.puntos == sudoku2.puntos) { menor = (sudoku1.archivo < sudoku2.archivo); }

	return menor;
}

