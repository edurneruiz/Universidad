#include <iostream>
#include<string>
#include <fstream>
#include "GestorSurtidores.h"
using namespace std;


bool resuelveCaso() {
	ifstream archivo;
	archivo.open("surtidor.txt");

	if (!archivo.is_open())
		return false;
	else {
		gestor a;
		string orden, surtidor, vehiculo, tipo_combustible; int num_litros;

		archivo >> orden;
		while (orden != "FIN") {
			try {
				if (orden == "annadir_surtidor") {
					archivo >> surtidor;
					a.annadir_surtidor(surtidor);
				}
				else if (orden == "cargar_surtidor") {
					archivo >> surtidor >> tipo_combustible >> num_litros;
					a.cargar_surtidor(surtidor, tipo_combustible, num_litros);
				}
				else if (orden == "poner_en_espera") {
					archivo >> surtidor >> vehiculo;
					a.poner_en_espera(vehiculo, surtidor);
				}
				else if (orden == "vender") {
					archivo >> surtidor >> tipo_combustible >> num_litros;
					std::pair<string, int> p = a.vender(surtidor, tipo_combustible, num_litros);
					cout << "SE HAN VENDIDO " + to_string(num_litros) + " DEL TIPO " + tipo_combustible
						+ " AL VEHICULO " + p.first + " DESDE EL SURTIDOR " + surtidor;
					cout << '\n';
				}
				else if (orden == "abandona") {
					archivo >> vehiculo;
					a.abandona(vehiculo);
				}
			}
			catch (domain_error e) {
				cout << e.what() << '\n';
			}
			archivo >> orden;
		}
	}
	cout << "---\n";
	archivo.close();
	return true;
}


int main() {
	resuelveCaso();
	system("pause");
	//while (resuelveCaso()){}
	return 0;
}