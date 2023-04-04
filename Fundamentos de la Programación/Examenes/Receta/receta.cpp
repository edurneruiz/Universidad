#include "receta.h"

//prototipos
bool aparece(tReceta const&r, tComponente const& comp, int & i);

tReceta crear() {
	tReceta r;
	r.cont = 0;
	r.lista = new tComponente[MAX_COMP];
	cout << "Introduce el nombre de la receta: ";
	getline(cin, r.nombre);
	return r;
}

bool insertar(tReceta & r, tComponente const& comp) {
	bool ex;
	int pos = 0;

	if (r.cont == MAX_COMP) { ex = false; }
	else {
		if (aparece(r, comp, pos)) { actualizarGramos(r.lista[pos - 1], devolverGramos(comp)); }
		else {
			igualarComponentes(r.lista[r.cont], comp);
			r.cont++;
		}
		ex = true;
	}

	return ex;
}

void muestra(tReceta const& r) {
	float calorias = 0;
	cout << "NOMBRE: " << r.nombre << endl;
	for (int i = 0; i < r.cont; i++) {
		muestra(r.lista[i]);
		calorias += calcularCalorias(r.lista[i]);
	}
	cout << "Total de calorias: " << calorias << " cal." << endl;
}

void eliminar(tReceta & r) {
	delete[] r.lista;
}

bool aparece(tReceta const&r, tComponente const& comp, int & i) {
	bool ap = false;

	while ((i < r.cont) && !ap) {
		ap = mismoComponente(r.lista[i], comp);
		i++;
	}


	return ap;
}