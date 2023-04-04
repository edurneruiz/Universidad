#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

//prototipos de funciones

int menu(); // el jugador elige el modo de juego
float modoA(ifstream& archivo, int numCartas); // juega en el modo A, devuelve la puntuacion total del jugador
float modoBhumano(ifstream& archivo, int numCartas);
float modoBmaquina(ifstream& archivo, int numCartas, float puntJugador);
int determinaGanador(float puntJugador, float puntMaquina);


int main() {

	int opc = menu(); //ejecuta la función para elegir el menú

	while (opc != 0) {

		ifstream archivo;
		string mazo;
		cout << "Nombre del archivo: ";
		cin >> mazo;
		int numCartas, ganador;
		float puntJugador, puntMaquina = 0;


		srand(time(NULL));
		numCartas = 3 + rand() % 3; //genera de forma aleatoria el numero de cartas //sabemos las vueltas que tendrá que dar un for


		if (opc == 1) {
			archivo.open(mazo);

			if (archivo.is_open()) {
				cout << "Turno del jugador: " << endl;
				puntJugador = modoA(archivo, numCartas);
				cout << "Puntuacion del jugador: " << puntJugador << endl;
				ganador = determinaGanador(puntJugador, puntMaquina);
				if (ganador == 2) {
					cout << "Mas de 7.5. Tu pierdes!" << endl;
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "Turno de la maquina: " << endl;
					puntMaquina = modoA(archivo, numCartas);
					cout << "Puntuacion de la maquina:  " << puntMaquina << endl;
					ganador = determinaGanador(puntJugador, puntMaquina);
					if (ganador == 1) {
						cout << "Tu ganas!" << endl;
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
		if (opc == 2) {
			archivo.open(mazo);

			if (archivo.is_open()) {

				cout << "Turno del jugador" << endl;
				cout << "Numero de cartas: " << numCartas << endl;
				puntJugador = modoBhumano(archivo, numCartas);
				ganador = determinaGanador(puntJugador, puntMaquina);
				if (ganador == 2) {
					cout << "Mas de 7.5. Tu pierdes!" << endl;
					cout << "La maquina gana!" << endl;

				}
				else {
					cout << "Turno de la maquina" << endl;
					puntMaquina = modoBmaquina(archivo, numCartas, puntJugador);
					ganador = determinaGanador(puntJugador, puntMaquina);
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

			archivo.close();

		}
		opc = menu();

	}
	return 0;
}



int menu() {
	int opc = -1;

	while ((opc < 0) || (opc > 2)) { // cambiar cuando añadamos modos
		cout << "1 - Modo A" << endl;
		cout << "2 - Modo B" << endl;
		cout << "0 - Salir" << endl;
		cout << "Elige el modo de juego: ";
		cin >> opc;

		if ((opc < 0) || (opc > 2)) {
			cout << "Opcion no valida." << endl;
		}
	}

	return opc;
}






float modoA(ifstream& archivo, int numCartas) {
	int num;
	float suma = 0, valor;
	for (int i = 0; i < numCartas; i++) {

		archivo >> num;

		if ((num == 10) || (num == 11) || (num == 12)) {
			valor = 0.5;
		}
		else {
			valor = num;
		}
		suma = suma + valor;
		cout << "Carta: " << num << "  Puntuacion: " << suma << endl;

	}

	return suma;
}



float modoBhumano(ifstream& archivo, int numCartas) {
	int num, i = 0;
	float suma = 0, valor;
	char c = 'x';

	while (c != 'N') {
		archivo >> num;
		if ((num == 10) || (num == 11) || (num == 12)) {
			valor = 0.5;
		}
		else {
			valor = num;
		}
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
		if ((num == 10) || (num == 11) || (num == 12)) {
			valor = 0.5;
		}
		else {
			valor = num;
		}
		suma = suma + valor;
		cout << "Carta: " << num << "  Puntuacion: " << suma << endl;
		i++;

	}
	cout << "Puntuacion del maquina: " << suma << endl;
	return suma;
}

int determinaGanador(float puntJugador, float puntMaquina) {
	int ganador;
	if ((puntJugador < 7.5) && (puntMaquina < 7.5)) {
		if (puntJugador < puntMaquina) {
			ganador = 2;
		}
		else {
			ganador = 1;
		}
	}
	else if ((puntJugador > 7.5) && (puntMaquina < 7.5)) {
		ganador = 2;
	}
	else if ((puntJugador < 7.5) && (puntMaquina > 7.5)) {
		ganador = 1;
		cout << "Mas de 7.5. La maquina pierde!" << endl;

	}
	
	else if (puntMaquina == puntJugador) {
		ganador = 1 + rand() % 2;
		cout << "Empate!Ganador elegido aleatoriamente." << endl;
	}
	return ganador;
}

		
	
	





