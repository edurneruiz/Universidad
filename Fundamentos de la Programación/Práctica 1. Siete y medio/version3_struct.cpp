#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

typedef double tCartasPorAparecer[8];
const int MAX = 40;
typedef int tTabla[MAX];
typedef struct {
	tTabla datos;
	int cont = 0;
} tConjuntoCartas;

//prototipos de funciones

int menu(); // el jugador elige el modo de juego
float calculaValor(int num); 
int determinaGanador(float puntJugador, float puntMaquina);
int determinaGanadorModoD(float puntJugador, float puntMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina);
void completarArray(tCartasPorAparecer cartas);
void vaciarArray(tCartasPorAparecer cartas, int carta);
bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas);
void inicializa(tConjuntoCartas & cartas); //crea el mazo ordenado
void crearMazo(tConjuntoCartas & mazo); // desordena el mazo
void sacarCarta(tConjuntoCartas & cartas, int & carta); //elimina la ultima carta de la lista y la devuelve
void modoDhumano(tConjuntoCartas & mazo, tCartasPorAparecer cartas, tConjuntoCartas & cartasHumano, float & puntos);
void modoDmaquina(tConjuntoCartas & mazo, tCartasPorAparecer cartas, float puntosHumano, tConjuntoCartas & cartasMaquina, float & puntos);
void mostrarMazo(tConjuntoCartas mazo); // muestra el mazo
void rellenarArchivo(ofstream & archivo, tConjuntoCartas cartas);

int main() {
	tCartasPorAparecer cartas;
	
	int opc = menu(), carta = 0, ganador, numPartida = 0;
	float puntJugador, puntMaquina, puntos;

	while (opc != 0) {

		puntMaquina = 0;
		numPartida++;
		switch (opc) {
		case 4:
		{
			puntos = 0;
			ofstream archivo;
			tConjuntoCartas mazo, cartasHumano, cartasMaquina;
			string partida; // esto hay q mejorarlo pq no va
			partida = numPartida;
			completarArray(cartas);
			inicializa(mazo);
			crearMazo(mazo);

			cout << "TURNO DEL JUGADOR" << endl;
			modoDhumano(mazo, cartas, cartasHumano, puntos);
			puntJugador = puntos;
			puntos = 0;
			ganador = determinaGanadorModoD(puntJugador, puntMaquina, cartasHumano, cartasMaquina);
			if (ganador == 2) {
				cout << "La maquina gana!" << endl;
			}
			else {
				cout << "TURNO DE LA MAQUINA" << endl;
				modoDmaquina(mazo, cartas, puntJugador, cartasMaquina, puntos);
				puntMaquina = puntos;
				ganador = determinaGanadorModoD(puntJugador, puntMaquina, cartasHumano, cartasMaquina);
				if (ganador == 2) {
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "Tu ganas!" << endl;
				}
			}
			archivo.open("mamut.txt");
			archivo << "Partida #" << numPartida << endl;
			archivo << "Ganador: ";
			if (ganador == 1) {
				archivo << "¡Humano!" << endl;
			}
			else {
				archivo << "¡Maquina!" << endl;
			}
			archivo << "Resultados humano: - Puntuacion: " << puntJugador << " -Cartas: ";
			rellenarArchivo(archivo, cartasHumano);
			archivo << endl;
			archivo << "Resultados maquina: - Puntuacion: " << puntMaquina << " -Cartas: ";
			rellenarArchivo(archivo, cartasMaquina);
			archivo.close();
		}
		break;
		default:
			cout << "Opcion no valida." << endl;
		}
		cout << endl;
		opc = menu();
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
	bool dep = true;
	
	for (int i = 0; i < 10; i++) {
		if (i == 0) {
			cartas.datos[i] = 1;
			cartas.cont++;
		}
		else if (i == 7) {
			cartas.datos[i] = 3 + cartas.datos[i - 1];
			cartas.cont++;
		}
		else {
			cartas.datos[i] = 1 + cartas.datos[i - 1];
			cartas.cont++;
		}
		for (int j = 1; j < 4; j++) {
			cartas.datos[i + 10 * j] = cartas.datos[i];
			cartas.cont++;
		}
	}
	if (dep == true) {
		cout << "[MAZO SIN BARAJAR... " << endl;
		mostrarMazo(cartas);
		cout << " FIN DE MAZO SIN BARAJAR]" << endl;
	}
}

void crearMazo(tConjuntoCartas & mazo) {
	int numAleatorio, aux;
	bool dep = true;
	
	srand(time(NULL));
	for (int i = 0; i < 40; i++) {
		numAleatorio = rand() % 40;
		aux = mazo.datos[numAleatorio];
		mazo.datos[numAleatorio] = mazo.datos[i];
		mazo.datos[i] = aux;
	}
	if (dep == true) {
		cout << "[MAZO TRAS BARAJAR... " << endl;
		mostrarMazo(mazo);
		cout << " FIN DE MAZO TRAS BARAJAR]" << endl;
	}
}

void sacarCarta(tConjuntoCartas & cartas, int & carta) {
	if (cartas.cont >= 1) {  //puedes sacar cartas si aun quedan en el mazo
		carta = cartas.datos[cartas.cont - 1];
		cartas.cont--;
	}
	else {
		cout << "No se puede robar mas, no quedan cartas." << endl;
	}
}

void annadirCarta(tConjuntoCartas & cartas, int carta) {
	cartas.datos[cartas.cont] = carta;
	cartas.cont++;
}

void modoDhumano(tConjuntoCartas & mazo, tCartasPorAparecer cartas, tConjuntoCartas & cartasHumano, float & puntos) {
	int num, i = 0;
	float valor;
	char c = 'x';
	bool dep = true;

	while (c != 'N') {

		sacarCarta(mazo, num);
		annadirCarta(cartasHumano, num);
		vaciarArray(cartas, num);
		valor = calculaValor(num);
		puntos = puntos + valor;
		
		if (dep == true) {
			cout << "[ESTADO DEL MAZO   ";
			for (int t = 0; t < mazo.cont; t++) {
				cout << mazo.datos[t] << " ";
			}
			cout << "]" << endl;
		}
		
		cout << "Cartas: ";
		for (int i = 0; i < cartasHumano.cont; i++) {
			cout << cartasHumano.datos[i] << " ";
		}
		cout << endl;

		cout << "Puntuacion: " << puntos << endl;
		if (puntos <= 7.5) {
			cout << "Continuar? (S/N) ";
			cin >> c;
		}
		else {
			c = 'N';
		}
	}
	cout << "Puntuacion del jugador: " << puntos << endl;
	cout << endl;

}

void modoDmaquina(tConjuntoCartas & mazo, tCartasPorAparecer cartas, float puntosHumano, tConjuntoCartas & cartasMaquina, float & puntos) {
	int num;
	float valor;
	bool tePasas = false, dep = true;

	while ((puntos <= puntosHumano) && (puntos <= 7.5) && (tePasas == false)) {
		sacarCarta(mazo, num);
		annadirCarta(cartasMaquina, num);
		vaciarArray(cartas, num);
		valor = calculaValor(num);

		puntos = puntos + valor;

		if (dep == true) {
			cout << "[ESTADO DEL MAZO   ";
			for (int t = 0; t < mazo.cont; t++) {
				cout << mazo.datos[t] << " ";
			}
			cout << "]" << endl;
		}

		cout << "Cartas: ";
		for (int i = 0; i < cartasMaquina.cont; i++) {
			cout << cartasMaquina.datos[i] << " ";
		}
		cout << endl;

		cout << "Puntuacion: " << puntos << endl;
		if (puntosHumano == puntos) {
			tePasas = esProbablePasarse(puntos, cartas);
		}
	}
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

int determinaGanadorModoD(float puntJugador, float puntMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina) {
	int ganador;
	if ((puntJugador <= 7.5) && (puntMaquina <= 7.5)) {
		if (puntJugador < puntMaquina) {
			ganador = 2;
		}
		else if (puntJugador > puntMaquina) {
			ganador = 1;
		}
		else if (puntMaquina == puntJugador) {
			if (cartasHumano.cont < cartasMaquina.cont) {
				ganador = 1;
			}
			else if (cartasHumano.cont > cartasMaquina.cont) {
				ganador = 2;
			}
			else if (cartasHumano.cont == cartasMaquina.cont) {
				ganador = 1 + rand() % 2;
				cout << "Empate! Ganador elegido aleatoriamente." << endl;
			}
		}
	}
	else if ((puntJugador >= 7.5) && (puntMaquina <= 7.5)) {
		ganador = 2;
		cout << "Mas de 7.5. Tu pierdes!" << endl;
	}
	else if ((puntJugador <= 7.5) && (puntMaquina >= 7.5)) {
		ganador = 1;
		cout << "Mas de 7.5. La maquina pierde!" << endl;
	}

	return ganador;
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

void completarArray(tCartasPorAparecer cartas) {
	cartas[0] = 12;

	for (int x = 1; x < 8; x++) {
		cartas[x] = 4;
	}
}

void vaciarArray(tCartasPorAparecer cartas, int carta) {
	if ((carta == 10) || (carta == 11) || (carta == 12)) {
		cartas[0] = cartas[0] - 1;
	}
	else {
		cartas[carta] = cartas[carta] - 1;
	}
}

void mostrarMazo(tConjuntoCartas mazo) {
	for (int t = 0; t < 4; t++) {
		for (int u = 0; u < 10; u++) {
			cout << mazo.datos[u + 10 * t] << " ";
		}
		cout << endl;
	}
}

void rellenarArchivo(ofstream & archivo, tConjuntoCartas cartas) {
	for (int i = 0; i < cartas.cont; i++) {
		archivo << cartas.datos[i] << " ";
	}
}