/*
Apellidos: Ruiz Huguet
Nombre: Edurne
DNI: xxx
Puesto: 16
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

const int i = 100;
typedef int tSecuencia[i];

//prototipos de funciones

int sumaValores(tSecuencia secuencia, int posicion1, int posicion2);
void rellenarArray(tSecuencia secuencia, int n, int x);

int main() {
	int n, x, posicion1, posicion2, m, j = 0;
	tSecuencia secuencia;
	ofstream archivo;
	cout << "Cuantos numeros quieres en la secuencia?: ";
	cin >> n;
	cout << "Cuantos numeros anteriores quieres sumar para calcular cada nuevo numero?: ";
	cin >> x;
	rellenarArray(secuencia, n, x);
	cout << "Hallemos el primero numero de la secuencia que ese pasa de uno dado." << endl;
	cout << "De cual debe pasarse?: ";
	cin >> m;

	while (secuencia[j] < m) {
		j++;
	}

	cout << "El primero que se pasa de " << m << " es el " << secuencia[j] << endl;

	cout << "Ahora guardamos la secuencia completa en fichero." << endl;

	archivo.open("salida.txt");
	for (int t = 0; t < n; t++) {
		archivo << secuencia[t] << endl;
	}
	archivo.close();
	cout << "Archivo guardado." << endl;

	system("pause");
	return 0;

}


	void rellenarArray(tSecuencia secuencia, int n, int x) {
		int suma = 0;
		secuencia[0] = 1;
		for (int j = 1; j < n; j++) {
			if (j <= x) {
				suma = 0;
				for (int t = 1; t <= j; t++) {

					suma = suma + secuencia[j - t];

				}
				secuencia[j] = suma;

			}
			else {
				suma = 0;
				secuencia[j] = sumaValores(secuencia, j - x, j);

			}
		}
	}





	int sumaValores(tSecuencia secuencia, int posicion1, int posicion2) {
		int suma = 0, x;
		x = posicion2 - posicion1;

		for (int t = 1; t <= x; t++) {
			suma = suma + secuencia[posicion2 - t];
		}

		return suma;
	}
