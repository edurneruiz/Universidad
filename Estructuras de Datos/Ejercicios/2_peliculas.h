// Edurne Ruiz

#ifndef PELICULAS_H
#define PELICULAS_H

#include <iostream>
#include <iomanip>
#include <stdexcept>  // invalid_argument
#include <string>
#include "1_horas.h"

class pelicula {
private:
	horas comienzo;
	horas duracion;
	horas fin;
	std::string titulo;
	
public:
	pelicula() {}
	// constructora
	pelicula(horas c, horas d, std::string t) {
		comienzo = c;
		duracion = d;
		fin = c + d;
		titulo = t;
	}
	// observadoras
	horas c() { return comienzo; }
	horas d() { return duracion; }
	horas f() { return fin; }
	std::string t() { return titulo; }

	// operador de comparación
	bool operator<(pelicula const& p) const {
		if (fin == p.fin) return titulo < p.titulo;
		return 3600*fin.hora() + 60*fin.minuto() + fin.segundo() < 3600 * p.fin.hora() + 60 * p.fin.minuto() + p.fin.segundo();
	}

	void read(std::istream & input = std::cin) {
		horas c, d;
		std::string t;
		input >> c >> d;
		getline(input, t);
		comienzo = c; duracion = d; fin = c + d; titulo = t;
	}

	void print(std::ostream& o = std::cout) const {
		o << std::setfill('0') << std::setw(2) << fin << std::setfill('0') << std::setw(2) << titulo;
	}
};

inline std::ostream & operator<<(std::ostream & salida, pelicula const& p) {
	p.print(salida);
	return salida;
}

inline std::istream & operator>>(std::istream & entrada, pelicula & p) {
	p.read(entrada);
	return entrada;
}

#endif
