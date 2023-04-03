#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int F = 3;
const int MAX_APUNTES = 500;

typedef int tFecha[F];
typedef struct {
	tFecha fecha;
	float importe;
	string concepto;
} tApunte;
typedef tApunte tCuenta[MAX_APUNTES];
typedef struct {
	tCuenta cuenta;
	int cont;
} tCuentat;

//prototipos de funciones

int menu();
void inicializarCuenta(tCuentat & cuenta);
bool cargarFichero(string fichero, tCuentat & cuenta);
float ultimoImporte(tCuentat & cuenta);
float gastoLuzAño(tCuentat & cuenta, int año);
void mostrarCuenta(tCuentat & cuenta);

int main() {
	tCuentat cuenta;
	string fichero = "fichero.txt";
	int opc = menu(), año;

	while (opc != 0) {
		switch (opc) {
		case 1:
		{
			inicializarCuenta(cuenta);
			if (!cargarFichero(fichero, cuenta)) { cout << "No se ha podido cargar el archivo" << endl; }
			else { cout << "Fichero cargado con exito." << endl; }
		}
		break;
		case 2:
		{
			cout << "El importe de la ultima nomina fue de " << ultimoImporte(cuenta) << " euros." << endl;
		}
		break;
		case 3:
		{
			cout << "Introduzca el año deseado: ";
			cin >> año;
			cout << "El gasto medio de luz en " << año << " fue de " << gastoLuzAño(cuenta, año) << " euros." << endl;
		}
		break;
		case 4:
		{
			mostrarCuenta(cuenta);
		}
		break;
		default:
		{
			cout << "Opcion no valida." << endl;
		}
		}
		cout << endl;
		opc = menu();

	}

	system("pause");
	return 0;
}

int menu() {
	int opc;

	cout << "1 - Cargar cuenta de fichero" << endl;
	cout << "2 - Importe de la última nómina" << endl;
	cout << "3 - Gasto medio de luz en un año" << endl;
	cout << "4 - Mostrar por pantalla" << endl;
	cout <<	"0 - Salir" << endl;
	cout << "Elige una opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

void inicializarCuenta(tCuentat & cuenta) {
	cuenta.cont = 0;
	for (int i = 0; i < MAX_APUNTES; i++) {
		for (int j = 0; j < F; j++) {
			cuenta.cuenta[i].fecha[j] = 0;
		}
		cuenta.cuenta[i].importe = 0;
		cuenta.cuenta[i].concepto = " ";
	}
}

bool cargarFichero(string fichero, tCuentat & cuenta) {
	bool ex;
	int i = 0;
	ifstream archivo;
	archivo.open(fichero);
	if (!archivo.is_open()) { ex = false; }
	else {
		archivo >> cuenta.cuenta[i].fecha[0];
		while ((cuenta.cuenta[i].fecha[0] != -1) && (i < MAX_APUNTES)) {
			archivo >> cuenta.cuenta[i].fecha[1];
			archivo >> cuenta.cuenta[i].fecha[2];
			archivo >> cuenta.cuenta[i].importe;
			archivo >> cuenta.cuenta[i].concepto;
			cuenta.cont++;
			i++;
			archivo >> cuenta.cuenta[i].fecha[0];
		}
		ex = true;
	}
	return ex;
}

float gastoLuzAño(tCuentat & cuenta, int año) {
	float gasto = 0, j = 0;
	bool enc = false;
	for (int i = 0; i < cuenta.cont; i++) {
		if ((cuenta.cuenta[i].fecha[2] == año) && (cuenta.cuenta[i].concepto == "Luz")) {
			gasto = gasto + (-1)*cuenta.cuenta[i].importe;
			enc = true;
			j++;
		}
	}
	gasto = gasto / j;
	if (!enc) { cout << "No se ha encontrado ningun gasto en luz en dicho año. "; }
	return gasto;
}

float ultimoImporte(tCuentat & cuenta) {
	float importe;
	int i = 0;
	bool enc = false;
	for (int i = 0; i < cuenta.cont; i++) {
		if (cuenta.cuenta[i].concepto == "Salario") {
			importe = cuenta.cuenta[i].importe;
		}
	}
	return importe;
}

void mostrarCuenta(tCuentat & cuenta) {
	cout << left << setw(11) << "FECHA" << setw(18) << "IMPORTE" << "CONCEPTO" << endl;
	for (int i = 0; i < cuenta.cont; i++) {
		cout << left << setw(3) << cuenta.cuenta[i].fecha[0] << setw(2) << cuenta.cuenta[i].fecha[1] << setw(6) << cuenta.cuenta[i].fecha[2];
		cout << left << setw(8) << cuenta.cuenta[i].importe << setw (10) << " Eur." << cuenta.cuenta[i].concepto << endl;
	}
}

