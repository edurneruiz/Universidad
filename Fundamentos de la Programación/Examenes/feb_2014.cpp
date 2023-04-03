#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int NP = 5;
const int NC = 4;
typedef enum {papeleria, alimentacion, limpieza, informatica} tClase;
typedef struct {
	string NIF;
	tClase clase;
	int pedidos;
	float gastos;
} tProveedor;
typedef tProveedor tClientes[NP+1];
typedef struct {
	tClase clase;
	float gastos;
} tGastC;
typedef tGastC tGastoXclase[NC];


//prototipos funciones
void inicializarClientela(tClientes clientela);
void inicializarGasto(tGastoXclase gasto);
bool cargar(tClientes clientela);
int menu();
void opcion1(tClientes clientela);
void buscarProveedor(tClientes clientela, string NIF, int & pos, bool & enc);
bool nuevoPedido(tClientes clientela, string NIF, float euros);
void guardarArchivo(tClientes clientela);
void opcion2(tClientes clientela);
void mostrarXintervalo(tClientes clientela, int min, int max);
void opcion3(tClientes clientela, tGastoXclase gasto);
void inicializarGasto(tGastoXclase gasto);
void rellenarGasto(tClientes clientela, tGastoXclase gasto);
void totalesXclase(tGastoXclase gasto);

int main() {
	tClientes clientela;
	tGastoXclase gasto;
	bool carga;
	int opc;

	inicializarClientela(clientela);
	carga = cargar(clientela);
	
	if (!carga) {
		cout << "La carga no ha tenido exito." << endl;
	}
	else {
		opc = menu();
		while (opc != 0) {
			switch (opc) {
			case 1: 
			{
				opcion1(clientela);
				guardarArchivo(clientela);
			}
			break;
			case 2:
			{
				opcion2(clientela);
			}
			break;
			case 3:
			{
				opcion3(clientela, gasto);
			}
			break;
			default:
			{
				cout << "Opcion no valida." << endl;
			}
			}
			opc = menu();
		}
	}
	return 0;
}

void inicializarClientela(tClientes clientela) {

	for (int i = 0; i < NP; i++) {
		clientela[i].gastos = 0;
		clientela[i].NIF = " ";
		clientela[i].pedidos = 0;
	}
}

bool cargar(tClientes clientela) {
	ifstream archivo;
	int aux, i = 0;
	bool exito;
	archivo.open("clientes.txt.txt");

	if (!archivo.is_open()) {
		exito = false;
	}
	else {
		archivo >> clientela[i].NIF;
		while ((clientela[i].NIF != "X") || (i < NP)) {
			archivo >> aux;
			clientela[i].clase = (aux == 0) ? papeleria : (aux == 1) ? alimentacion : (aux == 2) ? limpieza : informatica;
			archivo >> clientela[i].pedidos;
			archivo >> clientela[i].gastos;
			i++;
			archivo >> clientela[i].NIF;
		}
	}
	archivo.close();
	exito = (i == NP) ? true : false;

	return exito;
}

int menu() {
	int opc;

	cout << "1 - Nuevo pedido" << endl;
	cout << "2 - Proveedores con numero de pedidos en un intervalo" << endl;
	cout << "3 - Gastos por clase de proveedor" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;

	return opc;
}

void opcion1(tClientes clientela) {
	string NIF;
	float euros;
	int pos = 0;
	bool enc;

	cout << "Introduzca NIF: ";
	cin >> NIF;
	cout << "Introduzca la cantidad de euros: ";
	cin >> euros;
	
	enc = nuevoPedido(clientela, NIF, euros);
	if (!enc) {
		cout << "No se ha encontrado ningun proveedor con dicho NIF." << endl;
	}
	
}

void buscarProveedor(tClientes clientela, string NIF, int & pos, bool & enc) {

	while ((pos < NP) && !enc) {
		enc = (NIF == clientela[pos].NIF) ? true : false;
		pos++;
	}
	pos = (enc) ? pos - 1 : pos;
}

bool nuevoPedido(tClientes clientela, string NIF, float euros) {
	int pos = 0;
	bool enc = false;
	buscarProveedor(clientela, NIF, pos, enc);
	if (enc) {
		clientela[pos].pedidos++;
		clientela[pos].gastos = clientela[pos].gastos + euros;
	}

	return enc;
}

void guardarArchivo(tClientes clientela) {
	ofstream archivo;
	int aux, i = 0;
	archivo.open("clientes_mod.txt.txt");

	if (!archivo.is_open()) {
		cout << "No se ha podido abrir el archivo." << endl;
	}
	else {
		archivo << left << setw(5) << clientela[i].NIF;
		while ((clientela[i].NIF != "X") || (i < NP)) {
			aux = (clientela[i].clase == 0) ? papeleria : (clientela[i].clase == 1) ? alimentacion : (clientela[i].clase == 2) ? limpieza : informatica;
			archivo << left << setw(5) << aux;
			archivo << left << setw(5) << clientela[i].pedidos;
			archivo << left << setw(5) << clientela[i].gastos << endl;
			i++;
			archivo << left << setw(5) << clientela[i].NIF;
		}
	}
	archivo.close();
}

void opcion2(tClientes clientela) {
	int min, max;

	cout << "Introduzca el minimo del intervalo deseado: ";
	cin >> min;
	cout << "Introduzca el maximo del intervalo deseado: ";
	cin >> max;
	cout << "Los proveedores con un numero de pedidos en [" << min << ", " << max << "] son: " << endl;
	mostrarXintervalo(clientela, min, max);
}

void mostrarXintervalo(tClientes clientela, int min, int max) {
	string aux;
	for (int i = 0; i < NP; i++) {
		if ((min <= clientela[i].pedidos) && (clientela[i].pedidos <= max)) {
			aux = (clientela[i].clase == papeleria) ? "Papeleria" : (clientela[i].clase == alimentacion) ? "Alimentacion" : (clientela[i].clase == limpieza) ? "Limpieza" : "Informatica";
			cout << clientela[i].NIF;
			cout << "  " << aux;
			cout << "  " << clientela[i].pedidos;
			cout << "  " << clientela[i].gastos << endl;
		}
	}
}

void opcion3(tClientes clientela, tGastoXclase gasto) {
	inicializarGasto(gasto);
	rellenarGasto(clientela, gasto);
	totalesXclase(gasto);
}

void inicializarGasto(tGastoXclase gasto) {
	for (int i = 0; i < NC; i++) {
		gasto[i].gastos = 0;
	}
}

void rellenarGasto(tClientes clientela, tGastoXclase gasto) {
	for (int i = 0; i < NP; i++) {
		gasto[i].clase = (i == 0) ? papeleria : (i == 1) ? alimentacion : (i == 2) ? limpieza : informatica;
		switch (clientela[i].clase) {
		case 0:
		{
			gasto[0].gastos = gasto[0].gastos + clientela[i].gastos;
		}
		break;
		case 1:
		{
			gasto[1].gastos = gasto[1].gastos + clientela[i].gastos;
		}
		break;
		case 2:
		{
			gasto[2].gastos = gasto[2].gastos + clientela[i].gastos;
		}
		break;
		case 3:
		{
			gasto[3].gastos = gasto[3].gastos + clientela[i].gastos;
		}
		}
	}
}

void totalesXclase(tGastoXclase gasto) {
	string aux;
	for (int i = 0; i < NC; i++) {
		aux = (gasto[i].clase == papeleria) ? "Papeleria" : (gasto[i].clase == alimentacion) ? "Alimentacion" : (gasto[i].clase == limpieza) ? "Limpieza" : "Informatica";
		cout << aux << "    ";
		cout << gasto[i].gastos << endl;
	}
}