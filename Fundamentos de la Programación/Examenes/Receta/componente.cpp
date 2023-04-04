#include "componente.h"

//prototipos
void inicializar(tComponente & comp);


void inicializar(tComponente & comp) {
	comp.gramos = 0;
	comp.ing = NULL;
}


tComponente leeComponente(tListaIngredientes & i) {
	int pos;
	string ingrediente;
	tComponente comp;
	inicializar(comp);
	
	ingrediente = selectIngred(i);
	pos = buscarPos(i, ingrediente, pos, 0, devolverContador(i));
	igualarIngredientes(comp.ing, i, pos);

	cout << "Introduzca los gramos necesarios de dicho ingrediente: ";
	cin >> comp.gramos;

	return comp;
}


void muestra(tComponente const& comp) {
	cout << "     " << comp.gramos << " gr. de " << devolverNombre(*comp.ing) << endl;
}

tPtrIngrediente devolverIngrediente(tComponente const& comp) {
	return comp.ing;
}

float calcularCalorias(tComponente const& comp) {
	float total;
	total = (comp.gramos * devolverCalorias(*comp.ing)) / 100;
	return total;
}

void igualarComponentes(tComponente & c1, tComponente const& c2) {
	c1 = c2;
}
bool mismoComponente(tComponente const& c1, tComponente const& c2) {
	string ing1, ing2;
	ing1 = devolverNombre(*c1.ing);
	ing2 = devolverNombre(*c2.ing);
	return ing1 == ing2;
}

void actualizarGramos(tComponente & comp, float gram) {
	comp.gramos += gram;
}

float devolverGramos(tComponente const& comp) {
	return comp.gramos;
}