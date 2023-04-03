#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

const int N = 3;
const int N_Vect = 8;
typedef float tVector[N];
typedef struct {
	tVector vector;
	string nombre;
} tVectorCompleto;
typedef tVectorCompleto tLista[N_Vect];
typedef struct {
	tLista lista;
	int cont;
} tVectores;

//prototipo de funciones
int menu();
void leerVectores(tVectores & vectores);
void mostrarVectores(tVectores & vectores);
void mostrarVector(tVectores & vectores, int pos);
void sumarVectores(tVectores & vectores);
void restarVectores(tVectores & vectores);
float moduloVector(tVectores & vectores, int pos);
void productoEscalar(tVectores & vectores);
void normalizacionVector(tVectores & vectores);
void componenteMayor(tVectores & vectores, int pos);


int main() {
	tVectores vectores;
	float modulo;
	int opc = menu();

	while (opc != 0) {
		leerVectores(vectores);
		mostrarVectores(vectores);
		switch (opc) {
		case 1:
		{
			sumarVectores(vectores);
		}
		break;
		case 2: 
		{
			restarVectores(vectores);
		}
		break;
		case 3:
		{
			cout << "Los modulos de dichos vectores son: " << endl;
			for (int i = 0; i < vectores.cont; i++) {
				cout << "-" << vectores.lista[i].nombre << ": ";
				modulo = moduloVector(vectores, i);
				cout << modulo << " unidades." << endl;
			}
		}
		break;
		case 4:
		{
			productoEscalar(vectores);
		}
		break;
		case 5: 
		{
			normalizacionVector(vectores);
		}
		break;
		case 6: 
		{
			cout << "Las componentes de mayor valor de dichos vectores son: " << endl;
			for (int i = 0; i < vectores.cont; i++) {
				cout << "-" << vectores.lista[i].nombre << ": ";
				componenteMayor(vectores, i);
			}
		}
		break;
		default:
		{
			cout << "Opcion no valida!" << endl;
		}
		}
		opc = menu();
	}
	return 0;
}

int menu() {
	int opc;
	cout << endl;
	cout << "1. Suma de vectores" << endl;
	cout << "2. Resta de vectores" << endl;
	cout << "3. Módulo de un vector" << endl;
	cout << "4. Producto escalar de 2 vectores" << endl;
	cout << "5. Normalización de un vector" << endl;
	cout << "6. Obtención de la componente de mayor valor" << endl;
	cout << "0. Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;
	return opc;
}

void leerVectores(tVectores & vectores) {
	
	cout << "Cuantos vectores quiere introducir? (Menos de " << N_Vect << "): ";
	cin >> vectores.cont;

	for (int i = 0; i < vectores.cont; i++) {
		vectores.lista[i].nombre = "Vector " + to_string(i+1);
		cout << vectores.lista[i].nombre << ":" << endl;
		for (int j = 0; j < N; j++) {
			cout << " - Coordenada " << j+1 << ": ";
			cin >> vectores.lista[i].vector[j];
		}
		cout << endl;
	}
}

void mostrarVectores(tVectores & vectores) {
	for (int i = 0; i < vectores.cont; i++) {
		cout << "-" << vectores.lista[i].nombre;
		mostrarVector(vectores, i);
	}
	cout << endl;
}

void mostrarVector(tVectores & vectores, int pos) {
	cout << left << setw(3) << ": (";
	for (int j = 0; j < N; j++) {
		if (j == N - 1) {
			cout << vectores.lista[pos].vector[j] << ")" << endl;
		}
		else {
			cout << vectores.lista[pos].vector[j] << ", ";
		}
	}
}

void sumarVectores(tVectores & vectores) {
	cout << "La suma de dichos vectores es";
	for (int j = 0; j < N; j++) {
		vectores.lista[vectores.cont].vector[j] = 0;
		for (int i = 0; i < vectores.cont; i++) {
			vectores.lista[vectores.cont].vector[j] = vectores.lista[vectores.cont].vector[j] + vectores.lista[i].vector[j];
		}
	}
	mostrarVector(vectores, vectores.cont);
}

void restarVectores(tVectores & vectores) {
	cout << "La resta de dichos vectores es";
	for (int j = 0; j < N; j++) {
		for (int i = 1; i < vectores.cont - 1; i++) {
			vectores.lista[vectores.cont].vector[j] = vectores.lista[i].vector[j] + vectores.lista[i + 1].vector[j];
		}
		vectores.lista[vectores.cont].vector[j] = vectores.lista[0].vector[j] - vectores.lista[vectores.cont].vector[j];
	}
	mostrarVector(vectores, vectores.cont);
}

float moduloVector(tVectores & vectores, int pos) {
	float mod, aux = 0;
	for (int j = 0; j < N; j++) {
		aux = aux + pow(vectores.lista[pos].vector[j], 2);
	}
	mod = sqrt(aux);
	return mod;
}

void productoEscalar(tVectores & vectores) {
	int ind, prod = 0;
	cout << "El producto escalar de dichos vectores es ";
	for (int j = 0; j < N; j++) {
		ind = 1;
		for (int i = 0; i < vectores.cont; i++) {
			ind = ind * vectores.lista[i].vector[j];
		}
		prod = prod + ind;
	}
	cout << prod << "." << endl;
}

void normalizacionVector(tVectores & vectores) {
	float mod, Nvect = vectores.cont;
	cout << "Los vectores unitarios de misma direccion y sentido que los dados es: " << endl;
	for (int i = 0; i < Nvect; i++) {
		cout << "-" << vectores.lista[i].nombre << ": ";
		mod = moduloVector(vectores, i);
		for (int j = 0; j < N; j++) {
			vectores.lista[vectores.cont].vector[j] = (vectores.lista[i].vector[j]) / (mod);
		}
		mostrarVector(vectores, vectores.cont);
		vectores.cont++;
	}
}

void componenteMayor(tVectores & vectores, int pos) {
	int compMay = 0;
	for (int j = 0; j < N; j++) {
		compMay = (vectores.lista[pos].vector[j] >= vectores.lista[pos].vector[compMay]) ? j : compMay;
	}
	cout << "componente " << compMay + 1 << ", que es igual a " << vectores.lista[pos].vector[compMay] << endl;
}