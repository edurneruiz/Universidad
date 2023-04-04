#include "parcelas.h"
#include <iomanip>
using namespace std;

// prototipos
void inicializarListaParcelas(tParcelasTotal & p);
void ordenar(tParcelasTotal & parcelas, int pos);
//string coordenadas(int x, int y);
int buscarPos(tParcelasTotal const& parcelas, tParcela & p, int & pos, int ini, int fin);


bool operator< (const tParcela p1, const tParcela p2) {
	return p1.platanos < p2.platanos;
}

ostream& operator<< (ostream& o, const tParcela p) {
	o << left << setw(15) << p.id << setw(15) << coordenadas(p.fila, p.columna) << setw(15) << p.platanos << endl;
	return o;
}

tParcelasTotal crearParcelas(tPlantacion const& plantacion, int lado) {
	int i = 0, j, pos;
	tParcela p;
	tParcelasTotal parcelas;
	inicializarListaParcelas(parcelas);

	while (i < devolverFilas(plantacion)) {
		j = 0;
		while (j < devolverColumnas(plantacion)) {
			p.platanos = calcularPlatanosParcela(plantacion, i, j, lado);
			pos = (parcelas.cont == 0) ? 0 : buscarPos(parcelas, p, pos, 0, parcelas.cont-1);
			ordenar(parcelas, pos);
			parcelas.lista[pos] = new tParcela;
			parcelas.lista[pos]->id = devolverId(plantacion);
			parcelas.lista[pos]->fila = i;
			parcelas.lista[pos]->columna = j;
			parcelas.lista[pos]->platanos = p.platanos;
			j += lado;
			parcelas.cont++;
		}
		i += lado;
	}

	return parcelas;
}

void mostrarListaParcelas(tParcelasTotal const& parcelas, int pos) { // recursiva
	if (pos != parcelas.cont) {
		cout << *parcelas.lista[pos];
		mostrarListaParcelas(parcelas, pos+1);
	}
}

void ordenar(tParcelasTotal & parcelas, int pos) {

	for (int i = parcelas.cont; i > pos; i--) {
		parcelas.lista[i] = parcelas.lista[i - 1];
	}
}

void inicializarListaParcelas(tParcelasTotal & p) {
	p.cont = 0;
	for (int i = 0; i < tam_max; i++) { p.lista[i] = NULL; }
}

string coordenadas(int x, int y) {
	string c;
	c = "(" + to_string(x) + ", " + to_string(y) + ")";
	return  c;
}

int devolverPlatanos(tParcelasTotal const& p, int num) {
	return p.lista[num]->platanos;
}

int devolverContador(tParcelasTotal const& p) {
	return p.cont;
}

tParcela* devolverParcela(tParcelasTotal const& p, int num) {
	return p.lista[num];
}

int buscarPos(tParcelasTotal const& parcelas, tParcela & p, int & pos, int ini, int fin) {
	int mitad;
	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (p.platanos == parcelas.lista[mitad]->platanos) { pos = mitad; }
		else if (p < *parcelas.lista[mitad]) { pos = buscarPos(parcelas, p, pos, mitad + 1, fin); }
		else { pos = buscarPos(parcelas, p, pos, ini, mitad - 1); }
	}
	pos = (ini > fin) ? ini : pos;
	return pos;
}

tParcelasTotal mezclar(tParcelasTotal const& p1, tParcelasTotal const& p2) {
	int i = 0, j = 0, pos1, pos2;
	tParcelasTotal m;
	inicializarListaParcelas(m);

	while (m.cont < (p1.cont + p2.cont)) {
		if (p1.lista[i] != NULL) {
			pos1 = buscarPos(m, *p1.lista[i], pos1, 0, m.cont - 1);
			ordenar(m, pos1);
			m.lista[pos1] = p1.lista[i];
			m.cont++;
		}
		if (p2.lista[i] != NULL) {
			pos2 = buscarPos(m, *p2.lista[i], pos2, 0, m.cont - 1);
			ordenar(m, pos2);
			m.lista[pos2] = p2.lista[i];
			m.cont++;
		}
		i++;
	}

	return m;
}

void liberar(tParcelasTotal & parcelas) {
	for (int i = 0; i < parcelas.cont; i++) {
		delete parcelas.lista[i];
	}
}