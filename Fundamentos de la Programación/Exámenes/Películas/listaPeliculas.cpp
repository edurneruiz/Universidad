#include "listaPeliculas.h"

//prototipos
void inicializar(tPeliculasTotal & p);
int buscarPosGenero(tPeliculasTotal const& p, tPelicula const& pelicula, int & pos, int ini, int fin);
int buscarPosValoracion(tPeliculasTotal const& p, tPelicula const& pelicula, int & pos, int ini, int fin);
void desplazar(tPeliculasTotal & p, int pos);



void inicializar(tPeliculasTotal & p) {
	p.cont = 0;
	for (int i = 0; i < MAX_PELICULAS; i++) { p.lista[i] = NULL; }
}


bool cargar(tPeliculasTotal & p) {
	bool carga;
	ifstream archivo;
	archivo.open("peliculas.txt");

	if (!archivo.is_open()) { carga = false; }
	else {
		archivo >> p.cont;
		archivo.ignore('\1');
		for (int i = 0; i < p.cont; i++) {
			p.lista[i] = new tPelicula;
			archivo >> *p.lista[i];
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

tPeliculasTotal filtrarPorActor(tPeliculasTotal const& p, string actor) {
	int i = 0;
	tPeliculasTotal films;
	inicializar(films);

	for (int i = 0; i < p.cont; i++) {
		if (interviene(*p.lista[i], actor)) {
			films.lista[films.cont] = p.lista[i];
			films.cont++;
		}
	}

	return films;
}

void mostrar(tPeliculasTotal const& p) {
	cout << "LISTA DE PELICULAS" << endl;
	cout << "---" << endl;

	for (int i = 0; i < p.cont; i++) {
		mostrar(*p.lista[i]);
		cout << "---" << endl;
	}
}

tPeliculasTotal ordenarPorGenero(tPeliculasTotal & p) {
	int pos = 0;
	tPeliculasTotal gen;
	inicializar(gen);

	for (int i = 0; i < p.cont; i++) {
		if (gen.cont == 0) { gen.lista[0] = p.lista[0]; }
		else {
			pos = buscarPosGenero(gen, *p.lista[i], pos, 0, gen.cont - 1);
			desplazar(gen, pos);
			gen.lista[pos] = p.lista[i];
		}
		gen.cont++;
	}

	return gen;
}

tPeliculasTotal ordenarPorValoracion(tPeliculasTotal & p) {
	int pos = 0;
	tPeliculasTotal val;
	inicializar(val);

	for (int i = 0; i < p.cont; i++) {
		if (val.cont == 0) { val.lista[0] = p.lista[0]; }
		else {
			pos = buscarPosValoracion(val, *p.lista[i], pos, 0, val.cont - 1);
			desplazar(val, pos);
			val.lista[pos] = p.lista[i];
		}
		val.cont++;
	}


	return val;
}


int buscarPosGenero(tPeliculasTotal const& p, tPelicula const& pelicula, int & pos, int ini, int fin) {
	int mitad;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (compararPeliculasGenero(pelicula, *p.lista[mitad])) { pos = buscarPosGenero(p, pelicula, pos, ini, mitad - 1); }
		else { pos = buscarPosGenero(p, pelicula, pos, mitad + 1, fin); }
	}

	pos = (ini > fin) ? ini : pos;

	return pos;
}

int buscarPosValoracion(tPeliculasTotal const& p, tPelicula const& pelicula, int & pos, int ini, int fin) {
	int mitad;

	if (ini <= fin) {
		mitad = (ini + fin) / 2;
		if (pelicula < *p.lista[mitad]) { pos = buscarPosValoracion(p, pelicula, pos, mitad +1 ,fin); }
		else { pos = buscarPosValoracion(p, pelicula, pos, ini, mitad - 1); }
	}

	pos = (ini > fin) ? ini : pos;

	return pos;
}

void desplazar(tPeliculasTotal & p, int pos) {
	for (int i = p.cont; i > pos; i--) {
		p.lista[i] = p.lista[i - 1];
	}
}

void destruir(tPeliculasTotal & p) {
	for (int i = 0; i < p.cont; i++) {
		delete p.lista[i];
	}
}