#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
using namespace std;

const int max = 8;
const bool fich = true; // crear mazo de manera aleatoria (false) o cargarlo a partir de un fichero indicado (true)
const bool dep = true; // muestra en pantalla el contenido del mazo de cartas despu�s de crearlo y tras cualquier modificaci�n en �l (true) o no (false)
const int MAX = 40;

typedef double tCartasPorAparecer[max];
typedef int tTabla[MAX];
typedef struct {
	tTabla datos;
	int cont = 0;
} tConjuntoCartas;

//prototipos de funciones
int menu(); // el jugador elige el modo de juego
float calculaValor(int num); // recibe la carta robada y devuelve su valor
int determinaGanador(float puntJugador, float puntMaquina); // recibe las puntuaciones de jugador y maquina, y tras compararlas, devuelve el ganador (MODO A, B Y C)

// funciones modo A
float modoA(ifstream& archivo, int numCartas); //  recibe el archivo con el mazo y el numero de cartas a robar, calcula y devuelve la puntuaci�n

//funciones modo B
float modoBhumano(ifstream& archivo, int numCartas); // recibe el archivo con el mazo y el maximo numero de cartas a robar y juega el humano hasta que desee parar o se pase de 7.5. Devuelve la puntuaci�n del jugador
float modoBmaquina(ifstream& archivo, int numCartas, float puntJugador); //// recibe el archivo con el mazo y el maximo numero de cartas a robar y roba cartas mientras su puntuaci�n sea menor que la del jugador y que 7.5. Devuelve los puntos de la m�quina.

// funciones modo C y D
void completarArray(tCartasPorAparecer cartas); // recibe un array vacio y a cada valor posible le asigna el numero de cartas correspondiente
void vaciarArray(tCartasPorAparecer cartas, int carta); // modifica el array que recibe seg�n la carta que se haya robado
bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas); // recibe los puntos de la m�quina y el array de cartas que quedan en el mazo y calcula la probabilidad de pasarse de 7.5 robando una carta. Devuelve true si la probabilidad supera el 0.5 y false en caso contrario.

//funciones modo C
void modoChumano(ifstream& archivo, tCartasPorAparecer cartas, float& puntos); //  recibe el archivo con el mazo, el array que indica cuantas cartas hay de cada. Permite al jugador robar las cartas que quiera y se calcula su puntuaci�n, la cual se guarda en la variable por referencia. Se vac�a el array de cartas cada vez que se roba.
void modoCmaquina(ifstream& archivo, tCartasPorAparecer cartas, float puntosHumano, float& puntos);  //  recibe el archivo con el mazo, el array que indica cuantas cartas hay de cada. La m�quina roba cartas mientras su puntuaci�n sea menor que la del jugadoy y que 7.5 y que la probabilidad de pasarse no supere 0.5 (en caso de empate). A su vez se calcula su puntuaci�n, la cual se guarda en la variable por referencia. Se vac�a el array de cartas cada vez que se roba.

// funciones modo D
void inicializa(tConjuntoCartas & cartas); //crea el mazo ordenado, aumenta el contador por cada carta que se a�ade y lo guarda en el struct
void crearMazo(tConjuntoCartas & mazo); // baraja el mazo y lo guarda en el struct
void sacarCarta(tConjuntoCartas & cartas, int & carta); // elimina la ultima carta de la lista y la devuelve en la variable por referencia. El contador disminuye por cada carta que se elimina
void annadirCarta(tConjuntoCartas & cartas, int carta); // a�ade  la carta robada a un struct que guarda las cartas del jugador o de la maquina y aumenta su contador
void modoDhumano(tConjuntoCartas & mazo, tCartasPorAparecer cartas, tConjuntoCartas & cartasHumano, float & puntos); // funciona igual que el modoChumano pero utiliza el mazo generado y barajado y guarda las cartas que se roban en el struct de cartas del jugador
void modoDmaquina(tConjuntoCartas & mazo, tCartasPorAparecer cartas, float puntosHumano, tConjuntoCartas & cartasMaquina, float & puntos); // funciona igual que el modoCmaquina pero utiliza el mazo generado y barajado y guarda las cartas que se roban en el struct de cartas de la maquina
int determinaGanadorModoD(float puntJugador, float puntMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina); // recibe las puntuaciones y el numero de cartas de jugador y maquina , y tras compararlas, devuelve el ganador (MODO D)
void mostrarMazo(tConjuntoCartas cartas); // recibe un mazo de cartas y lo muestra en pantalla
void crearArchivo(tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina, int ganador, int numPartida, float puntJugador, float puntMaquina); // crea y escribe el archivo que registra cada partida
void leerCartas(tConjuntoCartas cartas, ofstream & archivo); // recibe las cartas de un mazo y las escribe en el archivo de salida

int main() {
	ifstream archivo;
	string deck;
	tCartasPorAparecer cartas;
	int opc = menu(), carta = 0, ganador, numPartida = 0, numCartas;
	float puntJugador, puntMaquina, puntos;
	srand(time(NULL));
	numCartas = 3 + rand() % 3;

	while (opc != 0) {

		if (((opc < 4) && (opc > 0)) || (fich)) {
			cout << "Nombre del archivo: ";
			cin >> deck;
		}
		cout << endl;
		puntMaquina = 0;
		puntos = 0;
		numPartida++;

		switch (opc) { 
		case 1:
		{
			archivo.open(deck);
			if (archivo.is_open()) {
				cout << "TURNO DEL JUGADOR " << endl;
				puntJugador = modoA(archivo, numCartas);
				cout << "Puntuacion del jugador: " << puntJugador << endl;
				ganador = determinaGanador(puntJugador, puntMaquina);
				if (ganador == 2) {
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "TURNO DE LA MAQUINA " << endl;
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
		break;
		case 2:
		{
			archivo.open(deck);
			if (archivo.is_open()) {
				cout << "TURNO DEL JUGADOR" << endl;
				cout << "Numero de cartas: " << numCartas << endl;
				puntJugador = modoBhumano(archivo, numCartas);
				ganador = determinaGanador(puntJugador, puntMaquina);
				if (ganador == 2) {
					cout << "Mas de 7.5. Tu pierdes!" << endl;
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "TURNO DE LA MAQUINA" << endl;
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
		break;
		case 3:
		{
			archivo.open(deck);
			if (archivo.is_open()) {

				completarArray(cartas);
				cout << "TURNO DEL JUGADOR" << endl;
				cout << "Numero de cartas: SIN LIMITES" << endl;
				modoChumano(archivo, cartas, puntos);
				puntJugador = puntos;
				ganador = determinaGanador(puntJugador, puntMaquina);
				if (ganador == 2) {
					cout << "La maquina gana!" << endl;
				}
				else {
					cout << "TURNO DE LA MAQUINA" << endl;
					puntos = 0;
					modoCmaquina(archivo, cartas, puntJugador, puntos);
					puntMaquina = puntos;
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
		break;
		case 4:
		{
			tConjuntoCartas mazo, cartasHumano, cartasMaquina;
			completarArray(cartas);

			if (fich) {
				archivo.open(deck);
				if (archivo.is_open()) {
					for (int j = 0; j < 40; j++) {
						archivo >> mazo.datos[j];
						mazo.cont++;
					}
				}
				archivo.close();
				if (dep) {
					cout << "[Mazo barajado: ";
					mostrarMazo(mazo);
					cout << "]" << endl;
				}
			}
			else {
				inicializa(mazo);
				crearMazo(mazo);
			}

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
			crearArchivo(cartasHumano, cartasMaquina, ganador, numPartida, puntJugador, puntMaquina);
		}
		break;
		default:
			cout << "Opcion no valida." << endl;
		}
		cout << endl;
		opc = menu();
	}
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
	cout << "Puntuacion de la maquina: " << suma << endl;
	return suma;
}

void modoChumano(ifstream& archivo, tCartasPorAparecer cartas, float& puntos) {
	int num, i = 0;
	float suma = 0, valor;
	char c = 'x';

	while (c != 'N') {
		archivo >> num;
		vaciarArray(cartas, num);
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
		vaciarArray(cartas, num);

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

void inicializa(tConjuntoCartas & cartas) {
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
	if (dep) {
		cout << "[Mazo sin barajar: ";
		mostrarMazo(cartas);
		cout << "]" << endl;
	}
}

void crearMazo(tConjuntoCartas & mazo) {
	int numAleatorio, aux;

	for (int i = 0; i < 40; i++) {
		numAleatorio = rand() % 40;
		aux = mazo.datos[numAleatorio];
		mazo.datos[numAleatorio] = mazo.datos[i];
		mazo.datos[i] = aux;
	}
	if (dep) {
		cout << "[Mazo barajado: ";
		mostrarMazo(mazo);
		cout << "]" << endl;
	}
}

void sacarCarta(tConjuntoCartas & cartas, int & carta) {
	if (cartas.cont >= 1) {  // puedes sacar cartas si aun quedan en el mazo
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

	while (c != 'N') {

		sacarCarta(mazo, num);
		annadirCarta(cartasHumano, num);
		vaciarArray(cartas, num);
		valor = calculaValor(num);
		puntos = puntos + valor;

		if (dep) { // para depurar
			cout << "[Estado del mazo...";
			mostrarMazo(mazo);
			cout << "]" << endl;
		}

		cout << "Cartas: ";
		mostrarMazo(cartasHumano);

		cout << " Puntuacion: " << puntos << endl;
		if (puntos <= 7.5) {
			cout << "Continuar? (S/N) ";
			cin >> c;
		}
		else {
			c = 'N';
		}
	}
	cout << "Puntuacion del jugador: " << puntos << endl;
}

void modoDmaquina(tConjuntoCartas & mazo, tCartasPorAparecer cartas, float puntosHumano, tConjuntoCartas & cartasMaquina, float & puntos) {
	int num;
	float valor;
	bool tePasas = false;

	while ((puntos <= puntosHumano) && (puntos <= 7.5) && (tePasas == false)) {
		sacarCarta(mazo, num);
		annadirCarta(cartasMaquina, num);
		vaciarArray(cartas, num);

		if (dep) {
			cout << "[Estado del mazo...";
			mostrarMazo(mazo);
			cout << "]" << endl;
		}
		valor = calculaValor(num);
		puntos = puntos + valor;

		cout << "Cartas: ";
		mostrarMazo(cartasMaquina);
		cout << " Puntuacion: " << puntos << endl;

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
	if ((puntJugador <= 7.5) && (puntMaquina <= 7.5)) {
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
	redondeo = round(diferencia+0.5);

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

void mostrarMazo(tConjuntoCartas cartas) {
	for (int t = 0; t < cartas.cont; t++) {
		cout << cartas.datos[t] << " ";
	}
}

void crearArchivo(tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina, int ganador, int numPartida, float puntJugador, float puntMaquina) {
	ofstream archivo;
	string partida;
	partida = "Partida" + to_string(numPartida) + ".txt";
	archivo.open(partida);
	archivo << "Partida #" << numPartida << endl;
	archivo << "Ganador: ";
	if (ganador == 1) {
		archivo << "�Humano!" << endl;
	}
	else {
		archivo << "�Maquina!" << endl;
	}
	archivo << "Resultados humano: - Puntuacion: " << puntJugador;
	leerCartas(cartasHumano, archivo);
	archivo << endl;
	archivo << "Resultados maquina: - Puntuacion: " << puntMaquina;
	leerCartas(cartasMaquina, archivo);
	archivo.close();
}

void leerCartas(tConjuntoCartas cartas, ofstream & archivo) {
	archivo << " -Cartas: ";
	for (int i = 0; i < cartas.cont; i++) {
		archivo << cartas.datos[i] << " ";
	}
}