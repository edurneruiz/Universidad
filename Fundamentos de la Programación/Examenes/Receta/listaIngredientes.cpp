#include "listaIngredientes.h"
#include <iomanip>

//prototipos
void inicializar(tListaIngredientes & i);
void desplazar(tListaIngredientes & i, int pos);
istream& operator >>(istream& i, tIngrediente& ing);
void mostrar(tListaIngredientes const& i);


void inicializar(tListaIngredientes & i) {
	i.cont = 0;
	for (int j = 0; j < MAX_INGREDIENTES; j++) { i.lista[j] = NULL; }
}

void insertar(tListaIngredientes & i, tIngrediente & ing) {
	int pos = 0;

	if (i.cont == 0) { i.lista[0] = new tIngrediente(ing); }
	else {
		pos = buscarPos(i, ing.nombre, pos, 0, i.cont);
		desplazar(i, pos);
		i.lista[pos] = new tIngrediente(ing);
	}
}

bool carga(tListaIngredientes & i) {
	tIngrediente aux;
	bool carga, centinela = false;
	ifstream archivo;
	archivo.open("ingredientes.txt");

	inicializar(i);
	if (!archivo.is_open()) { carga = false; }
	else {
		while ((i.cont < MAX_INGREDIENTES) && (!centinela)) {
			archivo >> aux;
			if (aux.calorias == -1) { centinela = true; }
			else { 
				insertar(i, aux);
				i.cont++; 
			}
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

string selectIngred(tListaIngredientes const& i) {
	int pos;
	string ing;
	
	mostrar(i);
	cout << "Introduzca el numero del ingrediente deseado: ";
	cin >> pos;
	ing = i.lista[pos - 1]->nombre;

	return ing;
}

int buscarPos(tListaIngredientes const& i, string nombre, int & pos, int ini, int fin) {
	int mitad;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (i.lista[mitad] != NULL) {
			if (nombre == i.lista[mitad]->nombre) { pos = mitad; }
			else if (nombre < i.lista[mitad]->nombre) { pos = buscarPos(i, nombre, pos, ini, mitad - 1); }
			else { pos = buscarPos(i, nombre, pos, mitad + 1, fin); }
		}
	}

	pos = (i.lista[(ini + fin) / 2] == NULL) ? ini : (ini > fin) ? ini : pos;

	return pos;
}

void desplazar(tListaIngredientes & i, int pos) {
	for (int j = i.cont; j > pos; j--) {
		i.lista[j] = i.lista[j - 1];
	}
}

istream& operator >>(istream& i, tIngrediente & ing) {
	i>> ing.calorias;
	i.ignore('\1');
	getline(i, ing.nombre);

	return i;
}

void mostrar(tListaIngredientes const& i) {
	cout << left << setw(23) << "NOMBRE " << "CALORIAS " << endl;
	for (int j = 0; j < i.cont; j++) {
		cout << left << j + 1 << ". " << setw(20) << i.lista[j]->nombre << i.lista[j]->calorias << " cal." << endl;
	}
}
	
int devolverContador(tListaIngredientes const& i) {
	return i.cont;
}

void igualarIngredientes(tPtrIngrediente & ing, tListaIngredientes const&i, int pos) {
	ing = i.lista[pos];
}

string devolverNombre(tIngrediente const& ing) {
	return ing.nombre;
}
float devolverCalorias(tIngrediente const& ing) {
	return ing.calorias;
}

void eliminar(tListaIngredientes & i) {
	for (int j = 0; j < i.cont; j++) {
		delete i.lista[j];
	}
}