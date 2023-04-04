#include "listaDias.h"

//prototipos
void inicializar(tListaDias & d);
void desplazar(tListaDias & d, int pos);

void inicializar(tListaDias & d) {
	d.cont = 0;
	for (int i = 0; i < MAX_DIAS; i++) { 
		d.lista[i] = NULL;
	}
}


bool carga(tListaDias & d) {
	int i = 0;
	bool carga;
	string fecha_aux;
	tVenta venta_aux;
	ifstream archivo;
	archivo.open("datos.txt");

	inicializar(d);
	if (!archivo.is_open()) { carga = false; }
	else {
		archivo >> fecha_aux;
		while ((i < MAX_DIAS) && (fecha_aux != "XXX")) {
			archivo >> venta_aux;
			insertaDia(d, fecha_aux, venta_aux);
			i++;
			archivo >> fecha_aux;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}


bool encuentra(tListaDias const& d, string fecha, int & pos, int ini, int fin) {
	bool enc = false;
	int mitad;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (fecha == d.lista[mitad]->fecha) { 
			pos = mitad;
			enc = true;
		}
		else if (fecha < d.lista[mitad]->fecha) {
			enc = encuentra(d, fecha, pos, ini, mitad - 1);
		}
		else { enc = encuentra(d, fecha, pos, mitad + 1, fin); }
	}
	pos = (ini > fin) ? ini : pos;

	return enc;
}

void insertaDia(tListaDias & d, string fecha, tVenta & venta) {
	int pos = 0;
	if (!encuentra(d, fecha, pos, 0, d.cont - 1)) {
		desplazar(d, pos);
		d.lista[pos] = new tDia;
		inicializar(d.lista[pos]->ventas);
		d.lista[pos]->fecha = fecha;
		d.cont++;
	}
	insertaVenta(d.lista[pos]->ventas, venta);
}

void desplazar(tListaDias & d, int pos) {
	tDia* aux = NULL;
	for (int i = d.cont; i > pos; i--) {
		aux = d.lista[i];
		d.lista[i] = d.lista[i - 1];
		d.lista[i - 1] = aux;
	}
	delete aux;
}

float totalVentas(tListaDias const& d) {
	float total = 0;
	for (int i = 0; i < d.cont; i++) {
		total += totalVentas(d.lista[i]->ventas);
	}
	return total;
}

void muestra(tListaDias const& d) {
	for (int i = 0; i < d.cont; i++) {
		cout << "-------" << endl;
		cout << "Dia: " << d.lista[i]->fecha << endl;
		muestra(d.lista[i]->ventas);
	}
}

void destruye(tListaDias & d) {
	for (int i = 0; i < d.cont; i++) {
		destruye(d.lista[i]->ventas);
		delete d.lista[i];
	}
}

