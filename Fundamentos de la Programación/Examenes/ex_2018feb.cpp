#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_LIBROS = 10;

typedef struct {
	int ISBN;
	string titulo;
	string autor;
	int ejem;
	int prestados;
} tLibro;
typedef tLibro tLibros[MAX_LIBROS];
typedef struct {
	tLibros libros;
	int cont;
} tBiblioteca;

//prototipos de funciones

void inicializarBiblioteca(tBiblioteca & biblioteca);
void cargarBiblioteca(tBiblioteca & biblioteca);
int menu();
void insertarEjemplar(tBiblioteca & biblioteca);
bool libroExistente(const tBiblioteca biblioteca, int isbn, int & pos);
void añadirLibro(tBiblioteca & biblioteca);
void mostrarBiblioteca(const tBiblioteca biblioteca);
void mostrarLibrosAutor(const tBiblioteca biblioteca);
bool autorExistente(const tBiblioteca biblioteca, string aut);
bool libroDisponible(const tBiblioteca biblioteca, int pos);
void prestamo(tBiblioteca & biblioteca);

int main() {
	int opc;
	tBiblioteca biblioteca;

	inicializarBiblioteca(biblioteca);
	cargarBiblioteca(biblioteca);
	opc = menu();

	while (opc != 0) {
		switch (opc) {
		case 1:
		{
			insertarEjemplar(biblioteca);
		}
		break;
		case 2:
		{
			mostrarBiblioteca(biblioteca);
		}
		break;
		case 3:
		{
			mostrarLibrosAutor(biblioteca);
		}
		break;
		case 4:
		{
			prestamo(biblioteca);
		}
		break;
		default:
		{
			cout << "Opcion no valida." << endl;
		}
		}
		opc = menu();
	}


	return 0;
}

void inicializarBiblioteca(tBiblioteca & biblioteca) {
	biblioteca.cont = 0;
	for (int i = 0; i < MAX_LIBROS; i++) {
		biblioteca.libros[i].ISBN = 0;
		biblioteca.libros[i].titulo = " ";
		biblioteca.libros[i].autor = " ";
		biblioteca.libros[i].ejem = 0;
		biblioteca.libros[i].prestados = 0;
	}
}

void cargarBiblioteca(tBiblioteca & biblioteca) {
	ifstream archivo;
	int i = 0;
	archivo.open("biblioteca.txt");

	if (!archivo.is_open()) { cout << "No se ha podido abrir el archivo." << endl; }
	else {
		archivo >> biblioteca.libros[i].ISBN;
		while ((i < MAX_LIBROS) && (biblioteca.libros[i].ISBN != -1)) {
			getline(archivo, biblioteca.libros[i].titulo);
			archivo >> biblioteca.libros[i].autor;
			archivo >> biblioteca.libros[i].ejem;
			archivo >> biblioteca.libros[i].prestados;
			biblioteca.cont++;
			i++;
			archivo >> biblioteca.libros[i].ISBN;
		}
	}
	archivo.close();
}

int menu() {
	int opc;

	cout << "1 - Insertar ejemplar de un libro" << endl;
	cout << "2 - Mostrar biblioteca" << endl;
	cout << "3 - Mostrar libros de un autor" << endl;
	cout << "4 - Prestamo" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

void insertarEjemplar(tBiblioteca & biblioteca) {
	int ejemplares, pos = 0, isbn;
	char resp;

	cout << "Introduzca ISBN del libro deseado: ";
	cin >> isbn;

	if (!libroExistente(biblioteca, isbn, pos)) { 
		cout << "No se ha podido encontrar ningun libro con dicho ISBN." << endl; 
		cout << "Desea añadir un nuevo libro a la biblioteca con dicho ISBN? (S/N): ";
		cin >> resp;
		if (resp = 'S') {
			biblioteca.libros[biblioteca.cont].ISBN = isbn;
			añadirLibro(biblioteca);
			biblioteca.cont++;
		}
	}
	else {
		cout << "Introduzca el numero de ejemplares a insertar: ";
		cin >> ejemplares;
		biblioteca.libros[pos].ejem = biblioteca.libros[pos].ejem + ejemplares;
		cout << endl;
	}
}

bool libroExistente(const tBiblioteca biblioteca, int isbn, int & pos) {
	bool ex = false;
	
	while ((pos < biblioteca.cont) && (!ex)) {
		if (isbn == biblioteca.libros[pos].ISBN) { ex = true; }
		else { pos++;  }
	}

	return ex;
}

void añadirLibro(tBiblioteca & biblioteca) {
	string titulo;
	cout << "Titulo: ";
	cin.ignore();
	getline(cin, biblioteca.libros[biblioteca.cont].titulo);
	cout << "Autor/a: ";
	cin >> biblioteca.libros[biblioteca.cont].autor;
	cout << "Numero de ejemplares disponibles: ";
	cin >> biblioteca.libros[biblioteca.cont].ejem;
	biblioteca.libros[biblioteca.cont].prestados = 0;
	cout << endl;
}

void mostrarBiblioteca(const tBiblioteca biblioteca) {
	cout << left << setw(12) << "ISBN" << setw(31) << "TITULO" << setw(10) << "AUTOR/A" << setw(15) << "EJEMPLARES" << "PRESTADOS" << endl;
	for (int i = 0; i < biblioteca.cont; i++) {
		cout << left << setw(11) << biblioteca.libros[i].ISBN << setw(32) << biblioteca.libros[i].titulo << setw(10) << biblioteca.libros[i].autor << setw(15) << biblioteca.libros[i].ejem << biblioteca.libros[i].prestados << endl;
	}
	cout << endl;
}

void mostrarLibrosAutor(const tBiblioteca biblioteca) {
	string aut;
	cout << "Inserte el apellido del autor deseado: ";
	cin >> aut;
	if (!autorExistente(biblioteca, aut)) { cout << "No existe ningun libro escrito por dicho autor." << endl; }
	else {
		for (int i = 0; i < biblioteca.cont; i++) {
			if (aut == biblioteca.libros[i].autor) { 
				cout << left << setw(35) << biblioteca.libros[i].titulo; 
				if (libroDisponible(biblioteca, i)) {
					cout << "Disponible" << endl;
				}
				else {
					cout << "No disponible" << endl;
				}
			}
		}
	}
	cout << endl;
}

bool autorExistente(const tBiblioteca biblioteca, string aut) {
	int i = 0;
	bool ex = false;

	while ((i < biblioteca.cont) && (!ex)) {
		if (aut == biblioteca.libros[i].autor) { ex = true; }
		else { i++; }
	}

	return ex;
}

bool libroDisponible(const tBiblioteca biblioteca, int pos) {
	bool disp;
	disp = (biblioteca.libros[pos].ejem > biblioteca.libros[pos].prestados) ? true : false;

	return disp;
}

void prestamo(tBiblioteca & biblioteca) {
	int pos = 0, isbn;
	cout << "Introduzca ISBN del libro deseado: ";
	cin >> isbn;
	if (libroExistente(biblioteca, isbn, pos)) {
		if (libroDisponible(biblioteca, pos)) {
			biblioteca.libros[pos].prestados++;
			cout << "Se ha efectuado el prestamo." << endl;
		}
		else { cout << "No esta disponible en estos momentos." << endl; }
	}
	cout << endl;
}

