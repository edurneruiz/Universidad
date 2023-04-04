#include "listaSudokus.h"
#include <iostream>
#include <fstream>
#include "checkML.h"

//Prototipos
void ordenar(tListaSudokus & lista, string a, int p, int i);


void creaListaVacia(tListaSudokus & lista) {
	lista.contador = 0;
	for (int i = 0; i < MAX_SUDOKUS; i++) {
		iniciaSudoku(lista.lista[i]);
	}
}


bool cargar(tListaSudokus & lista) {
	int i = 0, p;
	ifstream archivo;
	string arch;
	bool carga = false;
	archivo.open("listaSudokus.txt");

	creaListaVacia(lista);

	if (!archivo.is_open()) { carga = false; }
	else {
		archivo >> arch;
		while ((arch != " ") && i < MAX_SUDOKUS) {
			igualarArchivo(lista.lista[i], arch);
			archivo >> p;
			igualarPuntos(lista.lista[i], p);
			i++;
			lista.contador++;
			arch = " ";
			archivo >> arch;
		}
		carga = true;
	}
	archivo.close();
	return carga;
}

void mostrar(const tListaSudokus & lista) {
	cout << "LISTA DE SUDOKUS DISPONIBLES" << endl;
	for (int i = 0; i < lista.contador; i++) {
		cout << "Sudoku " << i + 1 << endl;
		mostrarSudoku(lista.lista[i]);
		cout << "-----------------" << endl;
	}
}

//version 2

bool guardar(const tListaSudokus & lista) { //almacena en el archivo el contenido de lista y devuelve booleano
	ofstream a;
	bool escrito;

	a.open("listaSudokus.txt");
	if (!a.is_open()) { escrito = false; }
	else {
		for (int i = 0; i < lista.contador; i++) {
			a << devuelveArchivo(lista.lista[i]) << " " << devuelvePuntos(lista.lista[i]) << endl;
		}
		escrito = true;
	}
	a.close();

	return escrito;
}


bool registrarSudoku(tListaSudokus & lista) {
	bool reg;
	string a;
	int p;
	tSudoku nuevo;

	if (lista.contador != MAX_SUDOKUS) {
		cout << "Introduce nombre del fichero: ";
		cin >> a;
		if (buscarFichero(lista, a)) {  
			cout << "Ya existe ese sudoku!" << endl;
			reg = false;
		}
		else {
			cout << "Introduce los puntos que permite conseguir: ";
			cin >> p;
			igualarArchivo(nuevo, a);
			igualarPuntos(nuevo, p);
			ordenar(lista, a, p, buscarPos(lista, nuevo));
			lista.contador++;
			reg = true;
		}
	}
	else { reg = false; }
	return reg;
}

bool buscarFichero(const tListaSudokus & lista, string a) {
	bool si = false;
	int i = 0;

	while ((!si) && i < lista.contador) {
		si = (devuelveArchivo(lista.lista[i]) == a);
		i++;
	}

	return si;
}

void ordenar(tListaSudokus & lista, string a, int p, int i) {
	for (int j = lista.contador; j > i; j--) {
		intercambiaSudoku(lista.lista[j], lista.lista[j - 1]);
	}
	igualarArchivo(lista.lista[i], a);
	igualarPuntos(lista.lista[i],p);
}

int buscarPos(const tListaSudokus & lista, const tSudoku & sudoku) {
	int m,pos = -1, ini = 0, fin = lista.contador -1;

	while (ini <= fin) {
		pos = (ini + fin) / 2;
		if (sudoku < lista.lista[pos]) { fin = pos - 1; }
		else { ini = pos + 1; }
	}
	return	pos = (ini != pos) ? pos + 1 : pos;
}

tSudoku cargar(tListaSudokus lista, int i) {
	tSudoku s;
	iniciaSudoku(s);
	s = (i == 0) ? s : lista.lista[i - 1];
	return s;
}