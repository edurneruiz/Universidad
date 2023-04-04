#include "listaEquipos.h"

//prototipos
void inicializar(tListaEquipos & e);
void ordenar(tListaEquipos & e, int num);


void inicializar(tListaEquipos & e) {
	e = NULL;
}

bool cargar(tListaEquipos & eq, int & num) {
	int pos = 0;
	bool carga;
	tEquipo aux;
	ifstream archivo;
	archivo.open("liga.txt");

	inicializar(eq);
	if (!archivo.is_open()) { carga = false; }
	else {
		archivo >> num;
		eq = new tEquipo[num];
		for (int i = 0; i < num; i++) {
			archivo >> eq[i].nombre;
			archivo >> eq[i].dinero;
			archivo >> eq[i].puntos;
			cargar(eq[i].plantilla, archivo);
		}
		ordenar(eq, num);
		carga = true;
	}
	archivo.close();

	return carga;
}

int buscar(tListaEquipos const& e, string equipo) {
	int pos = 0;
	bool enc = false;

	while ((e[pos].nombre != " ") && !enc) {
		enc = (e[pos].nombre == equipo);
		pos++;
	}
	pos = (enc) ? pos - 1 : -1;

	return pos;
}

void mostrar(tEquipo const& e) {
	cout << e.nombre << endl;
	cout << "     " << e.dinero << " euros" << endl;
	cout << "     " << e.puntos << " puntos" << endl;
	cout << "     " << "Jugadores: " << endl;
	mostrar(e.plantilla);
	cout << endl;
}

void mostrarDinero(tEquipo const& e) {
	cout << e.nombre << " (" << e.dinero << " euros)" << endl;
}

int elegir(tEquipo & eq) {
	int pos;

	mostrar(eq.plantilla);
	cout << "Elige jugador (por posicion): ";
	cin >> pos;

	return pos;
}

void liberar(tListaEquipos & e, int num) {
	for (int i = 0; i < num; i++) {
		liberar(e[i].plantilla);
	}
	delete[] e;
}

int buscarPos(tListaEquipos const& e, tEquipo const& equipo, int & pos, int ini, int fin) {
	int mitad;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (equipo.puntos == e[mitad].puntos) { pos = mitad; }
		else if (equipo.puntos < e[mitad].puntos) { pos = buscarPos(e, equipo, pos, mitad + 1, fin); }
		else { pos = buscarPos(e, equipo, pos, ini, mitad - 1); }
	}
	pos = (ini > fin) ? ini : pos;

	return pos;
}

bool dineroSuficiente(tEquipo const& comp, tEquipo const& vend, int pos) {
	bool si = !(jugadorMasCaro(comp.dinero, vend.plantilla, pos));
	return si;
}

void traspasar(tEquipo & comp, tEquipo & vend, int pos) {
	float ganancia;
	ganancia = venderJugador(comp.plantilla, vend.plantilla, pos);
	comp.dinero -= ganancia;
	vend.dinero += ganancia;
}

/*for
(int i=1;i<lista.contador; i++)
{
pos= i;
while ((pos>0)&& (lista.elementos[pos?1]> lista.elementos[pos]))
{
tmp= lista.elementos[pos];
lista.elementos[pos]= lista.elementos[pos ?1];
lista.elementos[pos ?1]= tmp;
pos??;
}
}*/

void ordenar(tListaEquipos & e, int num) {
	tEquipo aux;
	int pos;
	for (int i = 0; i < num; i++) {
		pos = i;
		while ((pos > 0) && (e[pos - 1].puntos < e[pos].puntos)) {
			aux = e[pos];
			e[pos] = e[pos - 1];
			e[pos - 1] = aux;
			pos--;
		}
	}
}