#include "listaVentas.h"

//prototipos
int buscarPos(tListaVentas const& v, tVenta const& venta, int & pos, int ini, int fin);
void desplazar(tListaVentas & v, int pos);

void inicializar(tListaVentas & v) {
	v.cont = 0;
	v.lista = new tVenta[MAX_VENTAS];
}

void insertaVenta(tListaVentas & v, tVenta & venta) {
	int pos = 0;
	if (v.cont == MAX_VENTAS) { cout << "La lista ya esta llena!" << endl;}
	else {
		pos = buscarPos(v, venta, pos, 0, v.cont - 1);
		desplazar(v, pos);
		v.lista[pos] = venta;
		v.cont++;
	}
}

void muestra(tListaVentas const& v) {
	for (int i = 0; i < v.cont; i++) {
		muestra(v.lista[i]);
	}
}

float totalVentas(tListaVentas const& v) {
	float total = 0;
	for (int i = 0; i < v.cont; i++) {
		total += totalVenta(v.lista[i]);
	}
	return total;
}

void destruye(tListaVentas const& v) {
	delete[] v.lista;
}

int buscarPos(tListaVentas const& v, tVenta const& venta, int & pos, int ini, int fin) {
	int mitad;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (venta == v.lista[mitad]) { pos = mitad; }
		else if (venta < v.lista[mitad]) { pos = buscarPos(v, venta, pos, ini, mitad - 1); }
		else { pos = buscarPos(v, venta, pos, mitad + 1, fin); }
	}
	pos = (ini > fin) ? ini : pos;

	return pos;
}

void desplazar(tListaVentas & v, int pos) {
	for (int i = v.cont; i > pos; i--) {
		v.lista[i] = v.lista[i - 1];
	}
}