#include <iostream>
using namespace std;

typedef struct {
	char nombre;
	int componente1;
	int componente2;
	int componente3;
	int componente4;
	int componente5;
} tVector;
typedef tVector tListaVectores[5];

typedef struct {
	tListaVectores datos;
	int contador;
} tListaVect;


// prototipos de funciones

int menu();
void leerVectores(tListaVect lista);
void mostrarVectores(tVector vector);
void sumaVectores(tListaVect lista);
void restaVectores(tListaVect lista);
int moduloVector(tVector vector);
int productoEscalar(tListaVect lista);
void normalizacion(tVector vector);
int componenteMayor(tVector vector);


int main() {
	int opc = menu();
	tListaVect lista;
	
	
	while (opc != 0) {

		leerVectores(lista);

		switch (opc) {
		case 1:
		{

		}
		break;
		default:
		{
			cout << "Opcion no valida." << endl;
		}
		}
	}


	system("pause");
	return 0;
}


int menu() {
	int opc = -1;

	cout << "Elige una operacion: " << endl;
	cout << "1. Suma de vectores" << endl;
	cout << "2. Resta de vectores" << endl;
	cout << "3. Módulo de un vector" << endl;
	cout << "4. Producto escalar de 2 vectores" << endl;
	cout << "5. Normalización de un vector" << endl;
	cout << "6. Obtención de la componente de mayor valor" << endl;	cout << "6. Salir" << endl;	cin >> opc;	return opc;
}

void leerVectores(tListaVect lista) {

	tVector vector;
	int x;

	cout << "Cuantos vectores quieres introducir? " << endl;
	cin >> x;
	cout << "Introduce " << x << " vectores de dimension 5: " << endl;

	for (int t = 0; t < x; t++) {
		cout << "Nombre del vector " << t << ": ";
		cin >> lista.datos[t].nombre;
		cout << "Introduce coordenadas del vector." << endl;
		cin >> lista.datos[t].componente1;
		cin >> lista.datos[t].componente2;
		cin >> lista.datos[t].componente3;
		cin >> lista.datos[t].componente4;
		cin >> lista.datos[t].componente5;

		mostrarVectores(vector);
	}
}

void mostrarVectores(tVector vector) {

	cout << "(" << vector.componente1 << ", " << vector.componente2 << ", " << vector.componente3 << ", " << vector.componente4 << ", " << vector.componente5 << ")" << endl;
}