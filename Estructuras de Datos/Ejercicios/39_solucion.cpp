#include <iostream>
#include <vector>
#include <string>
#include "libreria.h"
using namespace std;


void mostrar(vector<string> & v) {
	cout << "TOP10\n";

	for (int i = 0; i < v.size(); ++i) {
		cout << "   " << v[i] << "\n";
	}
}

bool resuelveCaso() {
	int n;

	cin >> n;
	if (!std::cin) return false;

	libreria i;
	string orden, titulo;
	int num;

	while (n > 0) {
		cin >> orden;
		try {
			if (orden == "nuevoLibro") {
				cin >> num;
				getline(cin, titulo);
				i.nuevoLibro(num, titulo);
			}
			else if (orden == "comprar") {
				getline(cin, titulo);
				i.comprar(titulo);
			}
			else if (orden == "numEjemplares") {
				getline(cin, titulo);
				try {
					num = i.numEjemplares(titulo);
					cout << "Existen " + to_string(num) + " ejemplares del libro" + titulo + "\n";
				}
				catch (invalid_argument e){
					cout << "No existe el libro" + titulo + " en el sistema \n";
				}
			}
			else if (orden == "estaLibro") {
				getline(cin, titulo);
				bool esta = i.estaLibro(titulo);

				if (esta) cout << "El libro" + titulo + " esta en el sistema \n";
				else cout << "No existe el libro" + titulo + " en el sistema \n";
			}
			else if (orden == "elimLibro") {
				getline(cin, titulo);
				i.elimLibro(titulo);
			}
			else if (orden == "top10") {
				vector<string> v = i.top10();
				mostrar(v);
			}
		}
		catch (invalid_argument e) {
			std::cout << e.what() << '\n';
		}
		catch (out_of_range e) {
			std::cout << e.what() << '\n';
		}
		--n;
	}
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}