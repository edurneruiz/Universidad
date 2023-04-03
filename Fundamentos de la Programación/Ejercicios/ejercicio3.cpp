#include <iostream>
#include <string>
using namespace std;


typedef enum {enero, febrero, marzo, abril, mayo, junio, julio, agosto, septiembre, octubre, noviembre, diciembre} tMes;
typedef struct {
	int dia;
	tMes mes;
	int año;
} tFecha;

//prototipos de funciones
void inicializarFecha(tFecha & fecha);
void pedirFecha(tFecha & fecha);
void determinarMes(tFecha & fecha, string m);
bool compararFechas(tFecha fecha1, tFecha fecha2, bool & mismoDia);

int main() {
	tFecha fecha1, fecha2;
	bool mayor, mismoDia = false;

	inicializarFecha(fecha1);
	inicializarFecha(fecha2);
	cout << "Introduzca la primera fecha: " << endl;
	pedirFecha(fecha1);
	cout << "Introduzca la segunda fecha: " << endl;
	pedirFecha(fecha2);
	mayor = compararFechas(fecha1, fecha2, mismoDia);
	if (!mismoDia) {
		(mayor) ? cout << "La primera fecha es mayor que la segunda." << endl : cout << "La segunda fecha es mayor que la primera." << endl;
	}
	
	system("pause");
	return 0;
}

void inicializarFecha(tFecha & fecha) {
	fecha.dia = 0;
	fecha.mes = enero;
	fecha.año = 0;
}

void pedirFecha(tFecha & fecha) {
	string m;
	
	cout << "Dia: ";
	cin >> fecha.dia;
	cout << "Mes: ";
	cin >> m;
	determinarMes(fecha, m);
	cout << "Año: ";
	cin >> fecha.año;
}

void determinarMes(tFecha & fecha, string m) {
	fecha.mes = (m == "Enero") ? enero : (m == "Febrero") ? febrero : (m == "Marzo") ? marzo : (m == "Abril") ? abril : (m == "Mayo") ? mayo : (m == "Junio") ? junio : (m == "Julio") ? julio : (m == "Agosto") ? agosto : (m == "Septiembre") ? septiembre : (m == "Octubre") ? octubre : (m == "Noviembre") ? noviembre : (m == "Diciembre") ? diciembre : enero;
}

bool compararFechas(tFecha fecha1, tFecha fecha2, bool & mismoDia) {
	bool mayor = false;
		
	if (fecha1.año > fecha2.año) {
		mayor = true;
	}
	else if (fecha1.año == fecha2.año) {
		if (fecha1.mes > fecha2.mes) {
			mayor = true;
		}
		else if (fecha1.mes == fecha2.mes) {
			if (fecha1.dia > fecha2.dia) {
				mayor = true;
			}
			else if (fecha1.dia == fecha2.dia) {
				cout << "Son el mismo dia!" << endl;
				mismoDia = true;
			}
		}
	}
	return mayor;
}