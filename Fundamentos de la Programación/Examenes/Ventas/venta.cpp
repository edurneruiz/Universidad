#include "venta.h"

//prototipos

void muestra(tVenta const& venta) {
	cout << left << "              " << venta.hora << setw(3) << ": " << setw(10) << venta.codigo << "-" << venta.unidades << " x " << venta.precio << " $ = " << totalVenta(venta) << " $" << endl;
}
float totalVenta(tVenta const& venta) {
	return venta.unidades*venta.precio;
}

bool operator==(tVenta const& v1, tVenta const& v2) {
	return v1.hora == v2.hora;
}
bool operator<(tVenta const& v1, tVenta const& v2) {
	return v1.hora < v2.hora;
}

istream& operator >>(istream& i, tVenta & venta) {
	i >> venta.hora;
	i >> venta.codigo;
	i >> venta.precio;
	i >> venta.unidades;
	return i;
}