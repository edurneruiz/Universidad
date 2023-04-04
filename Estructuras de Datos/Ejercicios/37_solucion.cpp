#include <iostream>
#include <vector>
#include "autoescuela.h"
using namespace std;


void mostrar(vector<string>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << "\n";
	}
}

bool resuelveCaso() {
	string orden;
	
	cin >> orden;
	if (!std::cin) return false;

	autoescuela a;
	string alumno, profesor;
	int n;
	while (orden != "FIN") {
		try {
			if (orden == "alta") {
				cin >> alumno >> profesor;
				a.alta(alumno, profesor);
			}
			else if (orden == "es_alumno") {
				cin >> alumno >> profesor;
				if (a.es_alumno(alumno, profesor)) 
					cout << alumno + " es alumno de " + profesor << "\n";
				else 
					cout << alumno + " no es alumno de " + profesor << "\n";
			}
			else if (orden == "puntuacion") {
				cin >> alumno;
				int p = a.puntuacion(alumno);
				cout << "Puntuacion de " + alumno + ": " << p << "\n";
			}
			else if (orden == "actualizar") {
				cin >> alumno >> n;
				a.actualizar(alumno, n);
			}
			else if (orden == "examen") {
				cin >> profesor >> n;
				vector<string> v = a.examen(profesor, n);
				cout << "Alumnos de " + profesor + " a examen: \n";
				mostrar(v);
			}
			else if (orden == "aprobar") {
				cin >> alumno;
				a.aprobar(alumno);
			}
		}
		catch (domain_error e) {
			std::cout << "ERROR" << '\n';
		}
		cin >> orden;
	}
	cout << "---\n";
	
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}