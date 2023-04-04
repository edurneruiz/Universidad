#include "pelicula.h"
#include <iomanip>

//prototipos




istream& operator>> (istream& i, tPelicula & pelicula){
	getline(i, pelicula.titulo);
	getline(i, pelicula.director);
	getline(i, pelicula.genero);
	i >> pelicula.valoracion;
	i >> pelicula.reparto;
	return i;
}

bool interviene(tPelicula const& pelicula, string actor) {
	int pos = 0;
	bool in;
	in = aparece(pelicula.reparto, actor, pos);
	return in;
}

void mostrar(tPelicula const& pelicula) {
	cout << left << setw(12) << "TITULO: " << pelicula.titulo << endl;
	cout << left << setw(12) << "DIRECTOR: " << pelicula.director << endl;
	cout << left << setw(12) << "GENERO: " << pelicula.genero << endl;
	cout << left << setw(12) << "VALORACION: " << setprecision(2) << pelicula.valoracion << endl;
}

bool operator<(tPelicula const& p1, tPelicula const& p2) {
	return p1.valoracion < p2.valoracion;
}


bool compararPeliculasGenero(tPelicula const& p1, tPelicula const& p2) {
	bool menor;

	if (p1.genero < p2.genero) { menor = true; }
	else if (p1.genero > p2.genero) { menor = false; }
	else {
		menor = !(p1.valoracion < p2.valoracion);
	}
	return menor;
}