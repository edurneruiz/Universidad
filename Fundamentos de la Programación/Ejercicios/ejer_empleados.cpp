#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int N = 10;
typedef enum { ESO, Bachillerato, FPmedio, FPsuperior, Grado, Master, Doctorado} tEstudio;
typedef enum {Fijo, Practicas, Eventual, Becario} tContratacion;
typedef struct {
	string nombre;
	int edad;
	tEstudio estudio;
	tContratacion contrato;
} tEmpleado;
typedef tEmpleado tEmpleados[N];
typedef struct {
	tEmpleados empleados;
	int cont;
} tPlantilla;

//prototipos de funciones
int menu();
void inicializarEmpresa(tPlantilla & plantilla);
void cargarArchivo(tPlantilla & plantilla);
void determinarEstudio(tPlantilla & plantilla, string est, int pos);
void determinarContrato(tPlantilla & plantilla, string cont, int pos);
void mostrarEmpleados(const tPlantilla plantilla);
string mostrarEstudio(const tPlantilla plantilla, int pos);
string mostrarContrato(const tPlantilla plantilla, int pos);
void eliminarFinal(tPlantilla & plantilla);
void eliminarPrincipio(tPlantilla & plantilla);
void añadirFinal(tPlantilla & plantilla);
void añadirPrincipio(tPlantilla & plantilla);
void añadirEmpleado(tPlantilla & plantilla, int pos);


int main() {
	int opc;
	tPlantilla plantilla;

	inicializarEmpresa(plantilla);
	cargarArchivo(plantilla);
	opc = menu();

	while (opc != 0) {
		switch (opc) {
		case 1: { mostrarEmpleados(plantilla); }
		break;
		case 2: { añadirFinal(plantilla); }
		break;
		case 3: { añadirPrincipio(plantilla); }
		break;
		case 4: { eliminarFinal(plantilla);	}
		break;
		case 5:	{ eliminarPrincipio(plantilla); }
		break;
		case 6: { inicializarEmpresa(plantilla); }
		break;
		default: { cout << "Opcion no valida" << endl; }
		}
		opc = menu();
	}

	return 0;
}

int menu() {
	int opc;

	cout << "1 - Mostrar empleados" << endl;
	cout << "2 - Anadir nuevo empleado al final de plantilla" << endl;
	cout << "3 - Anadir nuevo empleado al principio de plantilla" << endl;
	cout << "4 - Eliminar ultimo empleado" << endl;
	cout << "5 - Eliminar primer empleado" << endl;
	cout << "6 - Eliminar todos" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

void inicializarEmpresa(tPlantilla & plantilla) {
	plantilla.cont = 0;
	for (int i = 0; i < N; i++) {
		plantilla.empleados[i].edad = 0;
		plantilla.empleados[i].nombre = " ";
	}
}

void cargarArchivo(tPlantilla & plantilla) {
	int i = 0;
	string est, cont;
	ifstream archivo;
	archivo.open("plantilla.txt");

	if (!archivo.is_open()) { cout << "No se ha podido cargar el archivo." << endl; }
	else {
		archivo >> plantilla.empleados[i].nombre;
		while (plantilla.empleados[i].nombre != "XXX") {
			archivo >> plantilla.empleados[i].edad;
			archivo >> est;
			determinarEstudio(plantilla, est, i);
			archivo >> cont;
			determinarContrato(plantilla, cont, i);
			plantilla.cont++;
			i++;
			archivo >> plantilla.empleados[i].nombre;
		}
	}
}

void determinarEstudio(tPlantilla & plantilla, string est, int pos) {
	plantilla.empleados[pos].estudio = (est == "ESO") ? ESO : (est == "Bachillerato") ? Bachillerato : (est == "FPmedio") ? FPmedio : (est == "FPsuperior") ? FPsuperior : (est == "Grado") ? Grado : (est == "Master") ? Master : Doctorado;
}

void determinarContrato(tPlantilla & plantilla, string cont, int pos) {
	plantilla.empleados[pos].contrato = (cont == "Fijo") ? Fijo : (cont == "Practicas") ? Practicas : (cont == "Eventual") ? Eventual : Becario;
}

void mostrarEmpleados(const tPlantilla plantilla) {
	if (plantilla.cont != 0) {
		cout << left << setw(12) << "NOMBRE" << setw(8) << "EDAD" << setw(20) << "ESTUDIOS" << "CONTRATO" << endl;
		for (int i = 0; i < plantilla.cont; i++) {
			cout << left << setw(12) << plantilla.empleados[i].nombre << setw(8) << plantilla.empleados[i].edad << setw(20) << mostrarEstudio(plantilla, i) << mostrarContrato(plantilla, i) << endl;
		}
	}
	else { cout << "No se ha encontrado ningun empleado" << endl; }
	cout << endl;
}

string mostrarEstudio(const tPlantilla plantilla, int pos) {
	string aux;
	aux = (plantilla.empleados[pos].estudio == ESO) ? "ESO" : (plantilla.empleados[pos].estudio == Bachillerato) ? "Bachillerato" : (plantilla.empleados[pos].estudio == FPmedio) ? "FP grado medio" : (plantilla.empleados[pos].estudio == FPsuperior) ? "FP grado superior" : (plantilla.empleados[pos].estudio == Grado) ? "Grado" : (plantilla.empleados[pos].estudio == Master) ? "Master" : "Doctorado";
	return aux;
}

string mostrarContrato(const tPlantilla plantilla, int pos) {
	string aux;
	aux = (plantilla.empleados[pos].contrato == Fijo) ? "Fijo" : (plantilla.empleados[pos].estudio == Practicas) ? "En practicas" : (plantilla.empleados[pos].contrato == Eventual) ? "Eventual" : "Becario";
	return aux;
}

void eliminarFinal(tPlantilla & plantilla) {
	plantilla.cont--;
}

void eliminarPrincipio(tPlantilla & plantilla) {
	for (int i = 0; i < plantilla.cont; i++) {
		plantilla.empleados[i].nombre = plantilla.empleados[i + 1].nombre;
		plantilla.empleados[i].edad = plantilla.empleados[i + 1].edad;
		plantilla.empleados[i].contrato = plantilla.empleados[i + 1].contrato;
		plantilla.empleados[i].estudio = plantilla.empleados[i + 1].estudio;
	}
	plantilla.cont--;
}

void añadirFinal(tPlantilla & plantilla) {
	añadirEmpleado(plantilla, plantilla.cont);
	plantilla.cont++;
}

void añadirPrincipio(tPlantilla & plantilla) {
	for (int i = plantilla.cont; i > 0 ; i--) {
		plantilla.empleados[i].nombre = plantilla.empleados[i -1].nombre;
		plantilla.empleados[i].edad = plantilla.empleados[i -1].edad;
		plantilla.empleados[i].contrato = plantilla.empleados[i -1].contrato;
		plantilla.empleados[i].estudio = plantilla.empleados[i - 1].estudio;
	}
	añadirEmpleado(plantilla, 0);
	plantilla.cont++;
}

void añadirEmpleado(tPlantilla & plantilla, int pos) {
	string est, cont;
	if (pos < N) {
		cout << "Nombre del empleado: ";
		cin >> plantilla.empleados[pos].nombre;
		cout << "Edad del empleado: ";
		cin >> plantilla.empleados[pos].edad;
		cout << "Estudios cursados: ";
		cin >> est;
		determinarEstudio(plantilla, est, pos);
		cout << "Tipo de contrato: ";
		cin >> cont;
		determinarContrato(plantilla, cont, pos);
	}
	else { cout << "No se pueden añadir mas empleados!" << endl; }
	cout << endl;
}