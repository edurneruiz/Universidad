#include <iostream>
#include <string>
using namespace std;

const int Max = 100;


typedef struct {
	int dni;
	char letra;
} tNif;

typedef struct {
	string nombre;
	string apellidos;
	int edad;
	tNif nif;
} tPersona;

typedef tPersona tTablaPersonas[Max];

typedef struct {
	tTablaPersonas datos;
	int contador;
} tListaPersonas;

int main() {

	tListaPersonas personal;

	for (int i = 0; i < 3; i++) {
		
		cout << "Introduce nombre: ";
		cin >> personal.datos[i].nombre;
		cout << "Introduce apellido: ";
		cin >> personal.datos[i].apellidos;
		cout << "Introduce edad: ";
		cin >> personal.datos[i].edad;
		cout << "Introduce numero de dni: ";
		cin >> personal.datos[i].nif.dni;
		cout << "Introduce letra de nif: ";
		cin >> personal.datos[i].nif.letra;
	}
	

		cout << "Nombre de la tercera persona " << personal.datos[2].nombre << endl;

		cout << "Edad de la segunda persona: " << personal.datos[1].edad << endl;

		cout << "NIF de la primera persona: " << personal.datos[0].nif.dni << personal.datos[0].nif.letra << endl;

	
	

	system("pause");
	return 0;
}