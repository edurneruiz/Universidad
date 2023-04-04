#include <iostream>
#include <vector>
#include <string>
#include "consultorio_medico.h"
using namespace std;


void mostrar(vector<pair<string, fecha>> const& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i].first << " " << v[i].second << "\n";
	}
}

bool resuelveCaso() {
	int n;
	
	cin >> n;
	if (!std::cin) return false;

	consultorio c;
	string orden, medico, paciente;
	fecha f;
	int dia;
	for (int i = 0; i < n; ++i) {
		cin >> orden;
		try {
			if (orden == "nuevoMedico") {
				cin >> medico;
				c.nuevoMedico(medico);
			}
			else if (orden == "pideConsulta") {
				cin >> paciente >> medico >> f;
				c.pideConsulta(paciente, medico, f);
			}
			else if (orden == "siguientePaciente") {
				cin >> medico;
				string sig = c.siguientePaciente(medico);
				cout << "Siguiente paciente doctor " + medico + "\n";
				cout << sig << "\n";
			}
			else if (orden == "atiendeConsulta") {
				cin >> medico;
				c.atiendeConsulta(medico);
			}
			else if (orden == "listaPacientes") {
				cin >> medico >> dia;
				vector<pair<string, fecha>> v = c.listaPacientes(medico, dia);
				cout << "Doctor " + medico + " dia " + to_string(dia) + "\n";
				mostrar(v);
			}
		}
		catch (domain_error e) {
			std::cout << e.what() << '\n';
		}
	}
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}