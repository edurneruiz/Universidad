#include "cuadrillas.h"
#include <iomanip>

//prototipos de funciones




bool operator<(tCuadrilla const& c1, tCuadrilla const& c2) {
	return c1.max_p < c2.max_p;
}
ostream& operator<<(ostream& o, tCuadrilla const& c) {
	o << left << setw(15) << c.id << setw(15) << c.max_p << setw(15) << c.p->id << setw(15) << coordenadas(c.p->fila, c.p->columna) << setw(15) << c.p->platanos << endl;
	return o;
}
istream& operator>>(istream& i, tCuadrilla & c) {
	i >> c.id;
	i >> c.max_p;
	return i;
}

void inicializarListaCuadrillas(tCuadrillasTotal & cuadrillas) {
	cuadrillas.cont = 0;
	cuadrillas.lista = new tCuadrilla[MAX_CUADRILLAS];
}

tCuadrillasTotal crearListaCuadrillas() {
	ifstream archivo;
	tCuadrillasTotal cuadrillas;
	inicializarListaCuadrillas(cuadrillas);
	archivo.open("Cuadrillas.txt");

	if (!archivo.is_open()) { cout << "No se ha podido cargar el archivo de cuadrillas!" << endl; }
	else {
		archivo >> cuadrillas.cont;
		for (int i = 0; i < cuadrillas.cont; i++) {
			archivo >> cuadrillas.lista[i];
		}
	}
	archivo.close();

	return cuadrillas;
}

void asignarParcelas(tParcelasTotal const& parcelas, tCuadrillasTotal & cuadrillas) {
	int i = 0, j = 0, plat;

	while ((i < devolverContador(parcelas)) && (j < cuadrillas.cont)) {
		plat = 0;
		while (plat < devolverPlatanos(parcelas, i)) {
			plat += cuadrillas.lista[j].max_p;
			cuadrillas.lista[j].p = devolverParcela(parcelas, i);
			j++;
		}
		i++;
	}
	
}

void mostrarAsignaciones(tCuadrillasTotal const& cuadrillas) {
	cout << left << setw(15) << "CUADRILLA" << setw(15) << "CAPACIDAD" << setw(15) << "PLANTACION" << setw(15) << "PARCELA" << "PLATANOS A RECOGER" << endl;
	for (int i = 0; i < cuadrillas.cont; i++) {
		if (cuadrillas.lista[i].p != NULL) { cout << cuadrillas.lista[i]; }
	}
}

bool escribirCuadrillas(tCuadrillasTotal const& cuadrillas) {
	bool e;
	int i = 0;
	ofstream archivo;
	archivo.open("Salida.txt");

	if (!archivo.is_open()) { e = false; }
	else {
		archivo << left << setw(15) << "CUADRILLA" << setw(15) << "CAPACIDAD" << setw(15) << "PLANTACION" << setw(15) << "PARCELA" << "PLATANOS A RECOGER" << endl;
		while (i < cuadrillas.cont) {
			archivo << cuadrillas.lista[i];
			i++;
		}
		e = true;
	}
	archivo.close();

	return e;
}

void liberar(tCuadrillasTotal & cuadrillas) {
	delete[] cuadrillas.lista;
}