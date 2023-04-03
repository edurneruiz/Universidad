#include <iostream>
#include <fstream>

using namespace std;

//prototipos de funciones
bool esTriangular(int num); //indica si un numero es triangular o no

bool esTriangular(int num) {
	bool triang = false;
	int i = 1, calc;
	calc = (i*(i + 1) / 2);
	while (calc <= num) {
		if (num == calc) {
			triang = true;
		}
		i++;
		calc = (i*(i + 1) / 2);
	}
	return triang;
}

int main() {
	bool triangular;
	ifstream archivo;
	int num;
	archivo.open("enteros.txt");
	if (archivo.is_open()) {
		archivo >> num;
		while (num != 0) {
			triangular = esTriangular(num);
			if (triangular == true) {
				cout << num << " es triangular." << endl;
			}
			else {
				cout << num << " no es triangular." << endl;
			}
			archivo >> num;
		}
		
	}
	system("pause");
	return 0;
}