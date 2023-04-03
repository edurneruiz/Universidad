#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct {
	string codigo;
	string nombre;
	float precio;
	bool oferta;
}tProducto;

const int NUM_PRODUCTOS = 5, MAX_CESTA = 50;
typedef tProducto tCatalogo[NUM_PRODUCTOS];

typedef struct {
	string codigo;
	int cantidad;
	float precioTotal;
}tCesta;
typedef tCesta tCompra[MAX_CESTA];

typedef struct {
	tCompra compra;
	int cont;
} tCompraTotal;
 
// prototipos de funciones
int menu();
bool cargarDatos(tCatalogo catalogo);
void mostrarProductos(tCatalogo catalogo);
void llenarCesta(tCatalogo catalogo, tCompraTotal & compra);
bool estaEnCatalogo(tCatalogo catalogo, string codigo);
int posCesta(tCompraTotal & compra, string codigo);
float precioLinea(tCatalogo catalogo, tCompraTotal & compra, int i);
void mostrarCesta(tCatalogo catalogo, tCompraTotal & compra, tProducto producto, float & total);
void escribirArchivo(tCatalogo catalogo, tCompraTotal & compra);

int main() {
	tProducto producto;
	tCatalogo catalogo;
	tCompraTotal compra;
	float total;
	bool carga;
	compra.cont = 0;
	
	carga = cargarDatos(catalogo);
	if (carga) {
		int opc = menu();
		while (opc != 0) {

			switch (opc) {
			case 1:
			{
				mostrarProductos(catalogo);
				llenarCesta(catalogo, compra);
			}
			break;
			case 2:
			{
				total = 0;
				escribirArchivo(catalogo, compra);
				mostrarCesta(catalogo, compra, producto, total);
				cout << "Importe total: " << total << endl;
			}
			break;
			default: {
				cout << "Opción no válida" << endl;
			}
			}
			opc = menu();
		}
	}
	else cout << "No se ha podido cargar." << endl;

	return 0;
}

int menu() {
	int opc;

	cout << endl;
	cout << "1- Añadir productos a la cesta" << endl;
	cout << "2- Confirmar pedido" << endl;
	cout << "0- Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

bool cargarDatos(tCatalogo catalogo) {
	ifstream archivo;
	bool carga;
	archivo.open("productos.txt.txt");

	if (archivo.is_open()) {
		for (int i = 0; i < NUM_PRODUCTOS; i++) {
			archivo >> catalogo[i].codigo;
			if (catalogo[i].codigo != "XXX") {
				archivo >> catalogo[i].precio;
				archivo >> catalogo[i].oferta;
				getline(archivo, catalogo[i].nombre);
			}
		}
		carga = true;
	}
	else {
		carga = false;
	}
	archivo.close();
	return carga;
}

void mostrarProductos(tCatalogo catalogo) {
	cout << left << setw(20) << "PRODUCTO" << left << setw(20) << "CODIGO" << left << setw(20) << "PRECIO" << left << setw(20) << "OFERTA (1 si / 0 no) " << endl;
	for (int i = 0; i < NUM_PRODUCTOS; i++) {
		cout << left << setw(20) << catalogo[i].nombre;
		cout <<left<< setw(20) << catalogo[i].codigo;
		cout <<left<< setw(20) << catalogo[i].precio;
		cout << left << setw(20) << catalogo[i].oferta << endl;
	}
	cout << endl;
}

void llenarCesta(tCatalogo catalogo, tCompraTotal & compra) {
	string pr = "U";
	int pos;
	bool enc;

	cout << "Introduzca el codigo del producto deseado (XXX para terminar): ";
	cin >> pr;
	while (pr != "XXX") {
		enc = estaEnCatalogo(catalogo, pr);
		pos = posCesta(compra, pr);
		if (!enc) {
			cout << "El producto no se encuentra en el catalogo. " << endl;
		}
		else if (pos < compra.cont) {
			cout << "El producto ya ha sido seleccionado. Ha elegido " << compra.compra[pos].cantidad << " unidades." << endl;
			cout << "Desea actualizar el número de unidades? (S/N): ";
			cin >> pr;
			if (pr == "S") {
				cout << "Indique cuantas unidades desea: ";
				cin >> compra.compra[pos].cantidad;
			}
			else {
				cout << "Peticion anulada." << endl;
			}
		}
		else {
			compra.compra[pos].codigo = pr;
			cout << "Indique cuantas unidades desea: ";
			cin >> compra.compra[pos].cantidad;
			compra.cont++;
		}
		cout << endl;
		cout << "Introduzca el codigo de otro producto (XXX para terminar): ";
		cin >> pr;
	}

}

bool estaEnCatalogo(tCatalogo catalogo, string codigo) {
	int i = 0;
	bool encontrado = false;
	while ((i < NUM_PRODUCTOS) && (!encontrado)) {
		if (catalogo[i].codigo == codigo) {
			encontrado = true;
		}
		else { 
			encontrado = false;
		}
		i++;
	}
	return encontrado;
}

int posCesta(tCompraTotal & compra, string codigo) {
	int posicion = 0, i = 0; 
	bool encontrado = false;
	while ((i < compra.cont) && (!encontrado)) {
		if (compra.compra[i].codigo == codigo) {
			encontrado = true;
		}
		else {
			posicion++;
		}
		i++;
	}
	return posicion;
}

void mostrarCesta(tCatalogo catalogo, tCompraTotal & compra, tProducto producto, float & total) {
	float precio = 0;
	cout << left << setw(20) << "CODIGO" << left << setw(20) << "CANTIDAD" << left << setw(20) << "PRECIO " << endl;
	for (int i = 0; i < compra.cont; i++) {
		cout << left << setw(20) << compra.compra[i].codigo;
		cout << left << setw(20) << compra.compra[i].cantidad;
		precio = precioLinea(catalogo, compra, i);
		cout << left << setw(20) << precio << endl;
		total = total + precio;
	}
}

float precioLinea(tCatalogo catalogo, tCompraTotal & compra, int i) {
	float precio;
	int j = 0;
	bool encontrado = false;
	while ((j < NUM_PRODUCTOS) && (!encontrado)) {
		if (compra.compra[i].codigo == catalogo[j].codigo) {
			if (catalogo[j].oferta) {
				precio = (compra.compra[i].cantidad % 2 == 0) ? ((catalogo[j].precio*compra.compra[i].cantidad) / 2) : (((catalogo[j].precio*(compra.compra[i].cantidad - 1)) / 2) + catalogo[j].precio) ;
			}
			else {
				precio = catalogo[j].precio*compra.compra[i].cantidad;
			}
			encontrado = true;
		}
		j++;
	}
	return precio;
}

void escribirArchivo(tCatalogo catalogo, tCompraTotal & compra) {
	ofstream archivo;
	float precio; 
	archivo.open("compra.txt");
	archivo << left << setw(20) << "CODIGO" << left << setw(20) << "CANTIDAD" << left << setw(20) << "PRECIO " << endl;
	for (int i = 0; i < compra.cont; i++) {
		precio = precioLinea(catalogo, compra, i);
		archivo << left << setw(20) << compra.compra[i].codigo;
		archivo << left << setw(20) << compra.compra[i].cantidad;
		archivo << left << setw(20) << precio << endl;
	}
	archivo.close();
}