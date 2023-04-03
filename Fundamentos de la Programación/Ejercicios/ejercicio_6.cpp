#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX_LLAMADAS = 50, MAX_CLIENTES = 100;
typedef struct {
	string fecha;
	int duracion;
	float coste;
} tLlamada;
typedef tLlamada tListaLlamadas[MAX_LLAMADAS];
typedef struct {
	tListaLlamadas registro;
	int cont;
} tRegistro;
typedef struct {
	string NIF;
	float gastoTotal;
	tRegistro lista;
} tCliente;
typedef tCliente tListaClientes[MAX_CLIENTES];
typedef struct {
	tListaClientes clientela;
	int cont;
} tClientela;

// prototipos de funciones
void inicializarClientela(tClientela & clientes);
void cargarArchivo(tClientela & clientes);
int clienteExistente(tClientela & clientes, string NIF, bool & encontrado);
float costeLlamada(tClientela & clientes, int numCliente, int numLlamada);
void mostrarClientes(tClientela & clientes);


int main() {
	tClientela clientes;

	inicializarClientela(clientes);
	cargarArchivo(clientes);
	mostrarClientes(clientes);

	system("pause");
	return 0;
}

void inicializarClientela(tClientela & clientes) {
	clientes.cont = 0;
	for (int i = 0; i < MAX_CLIENTES; i++) {
		clientes.clientela[i].gastoTotal = 0;
		clientes.clientela[i].NIF = " ";
		clientes.clientela[i].lista.cont = 0;
		for (int j = 0; j < MAX_LLAMADAS; j++) {
			clientes.clientela[i].lista.registro[j].coste = 0;
			clientes.clientela[i].lista.registro[j].duracion = 0;
			clientes.clientela[i].lista.registro[j].fecha = " ";
		}
	}
}

void cargarArchivo(tClientela & clientes) {
	int numCliente, i = 0; 
	bool encontrado = false;
	string aux;
	ifstream archivo;
	archivo.open("llamadas.txt.txt");
	if (!archivo.is_open()) {
		cout << "El archivo no se ha podido cargar." << endl;
	}
	else {
		archivo >> clientes.clientela[i].NIF;
		while ((clientes.clientela[i].NIF != "X") && (aux != "X")) {
			archivo >> clientes.clientela[i].lista.registro[clientes.clientela[i].lista.cont].fecha;
			archivo >> clientes.clientela[i].lista.registro[clientes.clientela[i].lista.cont].duracion;
			clientes.clientela[i].lista.cont++;
			i = clientes.cont;
			archivo >> aux;
			if (aux != "X") {
				numCliente = clienteExistente(clientes, aux, encontrado);
				if (!encontrado) {
					i++;
					clientes.clientela[i].NIF = aux;
					clientes.cont++;
				}
				else { i = numCliente; }
			}
		}
	}
	archivo.close();
}

int clienteExistente(tClientela & clientes, string NIF, bool & encontrado) {
	int i = 0;
	encontrado = false;
	while ((i < clientes.cont) && !encontrado) {
		encontrado = (clientes.clientela[i].NIF == NIF) ? true : false;
		i++;
	}
	i = (i == 0) ? 0 : i - 1;
	return i;
}

float costeLlamada(tClientela & clientes, int numCliente, int numLlamada) {
	int minuto;
	minuto = (clientes.clientela[numCliente].lista.registro[numLlamada].duracion) / 60 + 1;
	clientes.clientela[numCliente].lista.registro[numLlamada].coste = 0.15 + 0.08*minuto;
	return clientes.clientela[numCliente].lista.registro[numLlamada].coste;
}

void mostrarClientes(tClientela & clientes) {
	float coste, suma;
	for (int i = 0; i <= clientes.cont; i++) {
		suma = 0;
		cout << clientes.clientela[i].NIF << endl;
		for (int j = 0; j < clientes.clientela[i].lista.cont; j++) {
			cout << clientes.clientela[i].lista.registro[j].fecha << "  ";
			cout << clientes.clientela[i].lista.registro[j].duracion << " seg.  ";
			coste = costeLlamada(clientes, i, j);
			cout << clientes.clientela[i].lista.registro[j].coste << " Eur." << endl;
			clientes.clientela[i].gastoTotal = clientes.clientela[i].gastoTotal + coste;
		}
		cout << "Coste total de las llamadas: " << clientes.clientela[i].gastoTotal << " Eur." << endl;
		cout << endl;
	}
}