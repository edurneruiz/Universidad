#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
#include <cmath>


const int MAX = 40;
typedef int tMazo[MAX];

typedef struct {
	tMazo cartas;
	int cont;
} tCartas;

typedef tCartas tTablaMazos[MAX];
typedef struct {
	tTablaMazos mamut;
	int cont;
} tConjuntoCartas;

//prototipos de funciones

int menu(); // el jugador elige el modo de juego
void inicializa(tConjuntoCartas & cartas); //crea el mazo ordenado
void crearMazo(tConjuntoCartas & mazo); // desordena el mazo
void sacarCarta(tConjuntoCartas & cartas, int & carta); //elimina la ultima carta de la lista y la devuelve

int main() {
	int opc = menu(), carta;
	tConjuntoCartas cartas;


	switch (opc) {
	case 4:
	{
		inicializa(cartas);
		crearMazo(cartas);

		for (int t = 0; t < 40; t++) {
			cout << cartas.mamut[0]. << " ";
		} // muestra el mazo barajado

		cout << cartas.contador << endl;
	}
	break;
	default:
		cout << "Opcion no valida." << endl;
	}

	system("pause");
	return 0;
}






int menu() {
	int opc = -1;

	cout << "1 - Modo A" << endl;
	cout << "2 - Modo B" << endl;
	cout << "3 - Modo C" << endl;
	cout << "4 - Modo D" << endl;
	cout << "0 - Salir" << endl;
	cout << "Elige el modo de juego: ";
	cin >> opc;


	return opc;
}

void inicializa(tConjuntoCartas & cartas) {
	
	for (int i = 0; i < 10; i++) {
		if (i == 0) {
			cartas.mamut[i] = 1;
		}
		else if (i == 7) {
			cartas.mamut[i] = 3 + cartas.mamut[i - 1];
		}
		else {
			cartas.mamut[i] = 1 + cartas.mamut[i - 1];
		}
		for (int j = 1; j <= 4; j++) {
			cartas.mamut[i + 10 * j] = cartas.mamut[i];
		}
		
	}
	
	
}

void crearMazo(tConjuntoCartas & mazo) {
	int numAleatorio, aux;
	srand(time(NULL));
	for (int i = 0; i < 40; i++) {
		numAleatorio = rand() % 40;
		aux = mazo.mamut[numAleatorio];
		mazo.mamut[numAleatorio] = mazo.mamut[i];
		mazo.mamut[i] = aux;
	}
}

void sacarCarta(tConjuntoCartas & cartas, int & carta) {
	carta = cartas.mamut[cartas.contador];
}
