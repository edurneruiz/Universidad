#include"listaJuguetes.h"
#include <string>
using namespace std;

// prototipos
void inicializar(tListaJuguetes & j, int num);
void ordenar(tListaJuguetes & j, int pos);
void actualizarContador(tListaJuguetes & j, tDecada decada);


void inicializar(tListaJuguetes & j, int num) {
	j.lista = new tJuguete[num];
	j.cont_50 = 0;
	j.cont_60 = 0;
	j.cont_70 = 0;
	j.cont_80 = 0;
}


bool cargar(tListaJuguetes & j) {
	bool carga;
	int num, pos = 0, decada;
	long int unidades;
	string id;
	float precio;
	ifstream archivo;
	archivo.open("juguetes.txt");

	if (!archivo.is_open()) { carga = false; }
	else {
		archivo >> num;
		inicializar(j, num);
		for (int i = 0; i < num; i++) {
			archivo >> id;
			archivo >> decada;
			archivo >> unidades;
			archivo >> precio;
			insertar(j, id, escDecada(decada), unidades, precio);
		}
		carga = true;
	}
	archivo.close();

	return carga;
}


long int contadorLista(tListaJuguetes const& j) {
	return j.cont_50 + j.cont_60 + j.cont_70 + j.cont_80;
}

void ordenar(tListaJuguetes & j, int pos) {

	for (int i = contadorLista(j); i > pos; i--) {
		j.lista[i] = j.lista[i - 1];
	}
}


bool buscar(tListaJuguetes const& j, string id, int & pos, int ini, int fin) {
	bool ex = false;
	int mitad;
	string juguete;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		juguete = devolverId(j.lista[mitad]);
		if (id == juguete) { 
			pos = mitad; 
			ex = true;
		}
		else if (id < juguete) { ex = buscar(j, id, pos, ini, mitad - 1); }
		else { ex = buscar(j, id, pos, mitad + 1, fin); }
	}

	pos = (ini > fin) ? ini : pos;

	return ex;
}

void insertar(tListaJuguetes & j, string id, tDecada decada, long int unidades, float precio) {
	int pos = 0;
	bool ex = buscar(j, id, pos, 0, contadorLista(j)-1);

	if (ex) { sumarUnidades(j.lista[pos], unidades); }
	else {
		if (contadorLista(j) == 0) { añadirJuguete(j.lista[0], id, decada, unidades, precio); }
		else {
			ordenar(j, pos);
			añadirJuguete(j.lista[pos], id, decada, unidades, precio);
		}
		actualizarContador(j, decada);
	}
}

void mostrar(tListaJuguetes const& j) {
	cout << left << setw(20) << "IDENTIFICADOR" << setw(10) << "DECADA" << setw(14) << "UNIDADES" << setw(20) << "Precio venta: " << "Precio base: " << endl;

	for (int i = 0; i < contadorLista(j); i++) {
		mostrarJuguete(j.lista[i]);
	}
}

void actualizarContador(tListaJuguetes & j, tDecada decada) {
	switch (decada) {
	case años50: {j.cont_50++; }
				 break;
	case años60: {j.cont_60++; }
				 break;
	case años70: {j.cont_70++; }
				 break;
	case años80: {j.cont_80++; }
	}
}

bool eliminar(tListaJuguetes & j, string id) {
	int pos;
	bool ex = buscar(j, id, pos, 0, contadorLista(j) - 1);

	if (ex) { 
		restarUnidades(j.lista[pos]); 
		ex = (devolverUnidades(j.lista[pos]) == 0);
	}

	return ex;
}

void liberar(tListaJuguetes & j) {
	delete[] j.lista;
}

tJuguete devolverJuguete(tListaJuguetes const& j, int pos) {
	return j.lista[pos];
}