#include "listaJugadores.h"
#include <iostream>

using namespace std;

//prototipos
int menu();
void opcion1(const tListaSudokus & lista_s, tListaJugadores & lista_j, tSudoku & sudoku);
void opcion3(tListaJugadores const& lista_j, tListaJugadores & lista_j_ord);
void guardar(const tListaSudokus & lista_s, tListaJugadores & lista_j);

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // deteccion fuga de memoria

	int opc; // el sudoku que elige el usuario, puntos que consigue el jugadorpues
	tListaSudokus lista_s;
	tListaJugadores lista_j, lista_j_ord;
	tSudoku sudoku;

	iniciaSudoku(sudoku);
	cout << "BIENVENIDO AL JUEGAZO DE TU VIDA" << endl;

	if (cargar(lista_s) && cargar(lista_j)) {
		opc = menu();
		while (opc != 0) {
			switch (opc) {
			case 1: { opcion1(lista_s, lista_j, sudoku); }
			break;
			case 2: { mostrar(lista_j);	}
			break;
			case 3: { opcion3(lista_j, lista_j_ord); }
			break;
			case 4: { registrarSudoku(lista_s);	}
			break;
			default: { cout << "Opcion no valida!" << endl;	}
			}
			cout << endl;
			opc = menu();
		}
		guardar(lista_s, lista_j);
	}
	else { cout << "No se han podido realizar las cargas!" << endl; }
	system("pause");
	return 0;
}

int menu() {
	int opc;
	cout << "QUE QUIERES HACER?" << endl;
	cout << "1. - Jugar" << endl;
	cout << "2. - Ver jugadores ordenados por identificador" << endl;
	cout << "3. - Ver jugadores ordenados por puntos" << endl;
	cout << "4. - Incorporar sudoku" << endl;
	cout << "0. - Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

void opcion1(const tListaSudokus & lista_s, tListaJugadores & lista_j, tSudoku & sudoku) {
	int s, puntos;
	mostrar(lista_s);
	cout << "Elige un sudoku (introduce numero): ";
	cin >> s;
	sudoku = cargar(lista_s, s);
	puntos = jugarUnSudoku(sudoku);
	if (puntos >= 0) { puntuarJugador(lista_j, puntos); }
}

void opcion3(tListaJugadores const& lista_j, tListaJugadores & lista_j_ord) {
	lista_j_ord = ordenarPorRanking(lista_j);
	mostrar(lista_j_ord);
	borrarListaJugadores(lista_j_ord);
}

void guardar(const tListaSudokus & lista_s, tListaJugadores & lista_j) {
	if (guardar(lista_j) && guardar(lista_s)) {
		cout << "Se han guardado las listas en los ficheros!" << endl;
		borrarJugadores(lista_j);
		borrarListaJugadores(lista_j);
	}
	else { cout << "ERROR: no se han podido guardar las listas!" << endl; }
}