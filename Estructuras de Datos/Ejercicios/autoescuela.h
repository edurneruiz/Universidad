#include <iostream>
#include <vector>
#include "hashmap_eda.h"
#include "set_eda.h"
using namespace std;

using profesor = string;
using alumno = string;
using puntos = int;

class autoescuela {
	using info_al = pair<profesor, puntos>;

	unordered_map<alumno, info_al> alumnos; //clave -> alumno de la autoescuela, valor-> su profesor y puntos que tiene
	unordered_map<profesor, set<alumno>> profs; //clave-> profesor de la autoescuela, valor-> conjunto de alumnos suyos

public:

	autoescuela() : profs() {}

	void alta(alumno const& a, profesor const& p) { 
		auto itA = alumnos.find(a);
		if (itA != alumnos.end()) { //el alumno ya existe
			profs[itA->valor.first].erase(a); //eliminamos al alumno de su anterior profesor
			profs[p].insert(a); //añadimos el alumno al nuevo profesor
			alumnos[a].first = p; //cambiamos el profesor del alumno
		}
		else {
			profs[p].insert(a); //añadimos el alumno al profesor
			alumnos[a].first = p; //asignamos el profesor al alumno
			alumnos[a].second = 0; // tiene 0 puntos porque no estaba matriculado
		}
	}

	bool es_alumno(alumno const& a, profesor const& p) { 
		return profs[p].count(a);
	}

	int puntuacion(alumno const& a) {
		auto itA = alumnos.find(a);
		if (itA == alumnos.end()) {
			throw domain_error("El alumno " + a + " no esta matriculado.");
		}
		else {
			return alumnos[a].second;
		}
	}

	void actualizar(alumno const& a, int n) {
		auto itA = alumnos.find(a);
		if (itA == alumnos.end()) {
			throw domain_error("El alumno " + a + " no esta matriculado.");
		}
		else {
			alumnos[a].second += n;
		}
	}

	vector<alumno> examen(profesor const& p, int n) {
		vector<alumno> l;
		auto itP = profs[p];
		auto itA = itP.begin();
		while (itA != itP.end()) {
			auto al = *itA;
			if (alumnos[al].second >= n)
				l.push_back(al);
			++itA;
		}
		return l;
	}

	void aprobar(alumno const& a) {
		auto itA = alumnos.find(a);
		if (itA == alumnos.end()) {
			throw domain_error("El alumno " + a + " no esta matriculado.");
		}
		else {
			auto al = alumnos[a];
			profs[al.first].erase(a); //eliminar al alumno de la lista de su profesor
			alumnos.erase(a);
		}
	}

};
