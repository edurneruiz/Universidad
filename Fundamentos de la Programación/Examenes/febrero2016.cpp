#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int NUM_CLIENTES = 8;
const int NUM_INTERVALOS = 7;

typedef enum { particular, PYME, industria } tCliente;
typedef struct {
	string contrato;
	float consumo;
	tCliente cliente;
} tInfo;
typedef tInfo tClientela[NUM_CLIENTES];
typedef struct {
	tClientela clientela;
	int cont;
} tClientelaTotal;
typedef struct {
	int intervalo;
	int frecPart;
	int frecPYME;
	int frecInd;
} tIntervalos;
typedef tIntervalos tTabla[NUM_INTERVALOS];
typedef struct {
	tTabla tabla;
	int cont;
} tIntervalosTotal;

// prototipos funciones
bool cargarIntervalos(tIntervalosTotal & tabla);
void cargarClientes(tClientelaTotal & clientela);
int buscarIntervalo(tIntervalosTotal & tabla, tClientelaTotal & clientela, int numClient);
void frecuenciasConsumo(tIntervalosTotal tabla, tClientelaTotal & clientela, int numClient, int pos);
void mostrarTabla(tIntervalosTotal & tabla);

int main() {
	int pos;
	tIntervalosTotal tabla;
	tClientelaTotal clientela;
	bool carga;

	carga = cargarIntervalos(tabla);
	if (!carga) {
		cout << "ERROR" << endl;
	}
	else {
		cargarClientes(clientela);
		for (int i = 0; i < clientela.cont; i++) {
			pos = buscarIntervalo(tabla, clientela, i);
			if (pos != -1) {
				frecuenciasConsumo(tabla, clientela, i, pos);
			}
		}
		mostrarTabla(tabla);
	}
	system("pause");
	return 0;
}

bool cargarIntervalos(tIntervalosTotal & tabla) {
	ifstream archivo;
	bool carga;
	int i = 0;
	tabla.cont = 0;
	archivo.open("intervalos.txt.txt");

	if (!archivo.is_open()) {
		carga = false;
	}
	else {
		archivo >> tabla.tabla[i].intervalo;
		while ((i < NUM_INTERVALOS) && (tabla.tabla[i].intervalo != -1)) {
			tabla.tabla[i].frecPart = 0;
			tabla.tabla[i].frecPYME = 0;
			tabla.tabla[i].frecInd = 0;
			i++;
			tabla.cont++;
			archivo >> tabla.tabla[i].intervalo;
		}
		carga = true;
	}
	archivo.close();
	return carga;
}

void cargarClientes(tClientelaTotal & clientela) {
	ifstream archivo;
	int i = 0, cliente;
	clientela.cont = 0;
	archivo.open("consumos.txt.txt");

	if (!archivo.is_open()) {
		cout << "No se han podido cargar los clientes!" << endl;
	}
	else {
		archivo >> clientela.clientela[i].consumo;
		while ((clientela.clientela[i].consumo != -1) && (i < NUM_CLIENTES)) {
			archivo >> cliente;
			clientela.clientela[i].cliente = (cliente == 0) ? particular : (cliente == 1) ? PYME : industria;
			getline(archivo, clientela.clientela[i].contrato);
			i++;
			archivo >> clientela.clientela[i].consumo;
			clientela.cont++;
		}
	}
}

int buscarIntervalo(tIntervalosTotal & tabla, tClientelaTotal & clientela, int numClient) {
	int pos, i = 0;
	bool encontrado = false;

	if (clientela.clientela[numClient].consumo < tabla.tabla[tabla.cont].intervalo) {
		while ((i < NUM_INTERVALOS) && (!encontrado)) {
			pos = (clientela.clientela[numClient].consumo <= tabla.tabla[i].intervalo) ? i : i++;
			encontrado = (pos == i) ? true : false;
		}
	}
	else {
		pos = -1;
	}
	return pos;
}

void frecuenciasConsumo(tIntervalosTotal tabla, tClientelaTotal & clientela, int numClient, int pos)
{
	if (clientela.clientela[numClient].cliente == particular) {
		tabla.tabla[pos].frecPart++;
	}
	else if (clientela.clientela[numClient].cliente == PYME) {
		tabla.tabla[pos].frecPYME++;
	}
	else {
		tabla.tabla[pos].frecInd++;
	}
}

void mostrarTabla(tIntervalosTotal & tabla) {
	cout << "Calculamos las frecuencias de consumo de los clientes de tipo PYME. " << endl;
	cout << "Tabla de frecuencias por consumo: " << endl;
	cout << "De 0 a 30: " << tabla.tabla[0].frecPYME << endl;
	for (int i = 1; i < tabla.cont; i++) {
		cout << "De " << tabla.tabla[i - 1].intervalo << " a " << tabla.tabla[i].intervalo << ": " << tabla.tabla[i].frecPYME << endl;
	}
}

