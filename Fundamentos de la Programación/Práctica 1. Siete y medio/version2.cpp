#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
#include <cmath>

//prototipos de funciones

int menu(); // el jugador elige el modo de juego
float modoA(ifstream& archivo, int numCartas); // juega en el modo A, devuelve la puntuacion total del jugador
float modoBhumano(ifstream& archivo, int numCartas);
float modoBmaquina(ifstream& archivo, int numCartas, float puntJugador);
int determinaGanador(float puntJugador, float puntMaquina);
float calculaValor(int num);

typedef double tCartasPorAparecer[8];

void modoChumano(ifstream& archivo, tCartasPorAparecer cartas, float& puntos); // el humano juega en modo C
void modoCmaquina(ifstream& archivo, tCartasPorAparecer cartas, float puntosHumano, float& puntos);
bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas);


int main() {
	int opc = menu(); //ejecuta la función para elegir el menú

	while (opc != 0) {

		ifstream archivo;
		string mazo;
		if ((opc < 5) && (opc > 0)) { //para que no pida el mazo si la opcion es no valida
			cout << "Nombre del archivo: ";
			cin >> mazo;
		}
		int numCartas, ganador; // version 1
		float puntosHumano, puntMaquina = 0, puntos = 0;


		srand(time(NULL));
		numCartas = 3 + rand() % 3;

		switch (opc) {
		case 1:
		{
			archivo.open(mazo);

			if (archivo.is_open()) {
				cout << "Turno del jugador: " << endl;
				puntosHumano = modoA(archivo, numCartas);
				cout << "Puntuacion del jugador: " << puntosHumano << endl;
				ganador = determinaGanador(puntosHumano, puntMaquina);
				if (ganador == 2) {
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "Turno de la maquina: " << endl;
					puntMaquina = modoA(archivo, numCartas);
					cout << "Puntuacion de la maquina:  " << puntMaquina << endl;
					ganador = determinaGanador(puntosHumano, puntMaquina);
					if (ganador == 1) {
						cout << "Tu ganas." << endl;

					}
					else {
						cout << "La maquina gana!" << endl;
					}
				}
			}
			else {
				cout << "ERROR: No se ha podido leer el archivo" << endl;
			}

			archivo.close();

		}
		break;

		case 2:
		{
			archivo.open(mazo);

			if (archivo.is_open()) {

				cout << "Turno del jugador" << endl;
				cout << "Numero de cartas: " << numCartas << endl;
				puntosHumano = modoBhumano(archivo, numCartas);
				ganador = determinaGanador(puntosHumano, puntMaquina);
				if (ganador == 2) {
					cout << "Mas de 7.5. Tu pierdes!" << endl;
					cout << "La maquina gana!" << endl;

				}
				else {
					cout << "Turno de la maquina" << endl;
					puntMaquina = modoBmaquina(archivo, numCartas, puntosHumano);
					ganador = determinaGanador(puntosHumano, puntMaquina);
					if (ganador == 2) {
						cout << "La maquina gana" << endl;
					}
					else {
						cout << "Tu ganas" << endl;
					}
				}
			}
			else {
				cout << "ERROR: No se ha podido leer el archivo" << endl;
			}

			archivo.close();





		}
		break;
		case 3:
		{
			tCartasPorAparecer cartas;
			archivo.open(mazo);
			if (archivo.is_open()) {

				cartas[0] = 12;

				for (int x = 1; x < 8; x++) {
					cartas[x] = 4;
				}


				cout << "Turno del jugador" << endl;
				cout << "Numero de cartas: SIN LIMITES" << endl;
				modoChumano(archivo, cartas, puntos);
				puntosHumano = puntos;
				ganador = determinaGanador(puntosHumano, puntMaquina);
				if (ganador == 2) {
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "Turno de la maquina" << endl;
					puntos = 0;
					modoCmaquina(archivo, cartas, puntosHumano, puntos);
					puntMaquina = puntos;
					ganador = determinaGanador(puntosHumano, puntMaquina);
					if (ganador == 2) {
						cout << "La maquina gana!" << endl;
					}
					else {
						cout << "Tu ganas!" << endl;
					}

				}
			}
			else {
				cout << "ERROR: No se ha podido leer el archivo" << endl;
			}
		}
		break;

		default:
		{
			cout << "Opcion no valida!" << endl;
		}
		}
		opc = menu(); //VUELVE A PEDIR OPCION
	}
	return 0;
}


//funciones comunes a los 3 modos

int menu() {
	int opc = -1;

	cout << "1 - Modo A" << endl;
	cout << "2 - Modo B" << endl;
	cout << "3 - Modo C" << endl;
	cout << "0 - Salir" << endl;
	cout << "Elige el modo de juego: ";
	cin >> opc;


	return opc;
}

float calculaValor(int num) {
	float valor;
	if ((num == 10) || (num == 11) || (num == 12)) {
		valor = 0.5;
	}
	else {
		valor = num;
	}
	return valor;
}

int determinaGanador(float puntJugador, float puntMaquina) {
	int ganador;
	if ((puntJugador < 7.5) && (puntMaquina < 7.5)) {
		if (puntJugador < puntMaquina) {
			ganador = 2;
		}
		else if (puntJugador > puntMaquina) {
			ganador = 1;
		}
		else if (puntMaquina == puntJugador) {
			ganador = 1 + rand() % 2;
			cout << "Empate! Ganador elegido aleatoriamente." << endl;
		}
	}
	else if ((puntJugador > 7.5) && (puntMaquina < 7.5)) {
		ganador = 2;
		cout << "Mas de 7.5. Tu pierdes!" << endl;
	}
	else if ((puntJugador < 7.5) && (puntMaquina > 7.5)) {
		ganador = 1;
		cout << "Mas de 7.5. La maquina pierde!" << endl;
	}

	return ganador;
}

//funciones del modo A

float modoA(ifstream& archivo, int numCartas) {
	int num;
	float suma = 0, valor;
	for (int i = 0; i < numCartas; i++) {

		archivo >> num;
		valor = calculaValor(num);

		suma = suma + valor;
		cout << "Carta: " << num << "  Puntuacion: " << suma << endl;

	}

	return suma;
}

//funciones del modo B

float modoBhumano(ifstream& archivo, int numCartas) {
	int num, i = 0;
	float suma = 0, valor;
	char c = 'x';

	while (c != 'N') {
		archivo >> num;
		valor = calculaValor(num);
		suma = suma + valor;
		cout << "Carta: " << num << "  Puntuacion: " << suma << endl;
		i++;
		if ((suma < 7.5) && (i < numCartas)) {
			cout << "Continuar? (S/N)";
			cin >> c;
		}
		else { c = 'N'; }
	}
	cout << "Puntuacion del jugador: " << suma << endl;
	return suma;
}

float modoBmaquina(ifstream& archivo, int numCartas, float puntJugador) {
	int num, i = 0;
	float suma = 0, valor;


	while ((suma <= puntJugador) && (suma <= 7.5) && (i < numCartas)) {
		archivo >> num;
		valor = calculaValor(num);
		suma = suma + valor;
		cout << "Carta: " << num << "  Puntuacion: " << suma << endl;
		i++;

	}
	cout << "Puntuacion del maquina: " << suma << endl;
	return suma;
}

//funciones del modo C

void modoChumano(ifstream& archivo, tCartasPorAparecer cartas, float& puntos) {
	int num, i = 0;
	float suma = 0, valor;
	char c = 'x';

	while (c != 'N') {
		archivo >> num;

		if ((num == 10) || (num == 11) || (num == 12)) {
			cartas[0] = cartas[0] - 1;
			cout << cartas[0] << endl;
		}
		else {
			cartas[num] = cartas[num] - 1;
			cout << cartas[num] << endl;
		}

		valor = calculaValor(num);
		puntos = puntos + valor;
		cout << "Carta: " << num << "  Puntuacion: " << puntos << endl;
		i++;
		if (puntos < 7.5) {
			cout << "Continuar? (S/N)";
			cin >> c;
		}
		else {
			c = 'N';
		}
	}
	cout << "Puntuacion del jugador: " << puntos << endl;

}

void modoCmaquina(ifstream& archivo, tCartasPorAparecer cartas, float puntosHumano, float& puntos) {
	int num, i = 0;
	float valor;
	bool tePasas = false;

	while ((puntos <= puntosHumano) && (puntos <= 7.5) && (tePasas == false)) {
		archivo >> num;

		if ((num == 10) || (num == 11) || (num == 12)) {
			cartas[0] = cartas[0] - 1;
		}
		else {
			cartas[num] = cartas[num] - 1;
		}

		valor = calculaValor(num);
		puntos = puntos + valor;
		cout << "Carta: " << num << "  Puntuacion: " << puntos << endl;

		if (puntosHumano == puntos) {
			tePasas = esProbablePasarse(puntos, cartas);
		}
		i++;
	}
	cout << "Puntuacion de la maquina: " << puntos << endl;

}

bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas) {
	bool probable;
	float diferencia, suma = 0, total = 0, probabilidad;
	int redondeo;
	diferencia = 7.5 - puntosMaquina;
	redondeo = round(diferencia);


	for (int i = 0; i < 8; i++) {
		total = total + cartas[i];
	}

	for (int j = redondeo; j < 8; j++) {
		suma = suma + cartas[j];
	}

	probabilidad = suma / total;

	if (probabilidad < 0.5) {
		probable = false;
	}
	else {
		probable = true;
	}

	return probable;
}



