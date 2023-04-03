//Sopa.cpp : Este archivo contiene la función "main".La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

typedef string tTablero[6];

typedef struct {
	tTablero sopa;
	int alto;
	int ancho;
}tSopa;

typedef struct {
	int x;
	int y;
}tCoor;

typedef tCoor tDireccion[8];

//prototipos
void inicializarSopa(tSopa & s);
void mostrarSopa(tSopa const& s);
void dirs(tDireccion & dirs);
bool compruebaPosDir(tSopa s, string pal, tCoor pos, tCoor dir);
bool buscaDir(tSopa s, string pal, tCoor pos, tCoor & dir);
bool buscaPal(tSopa s, string pal, tCoor & pos, tCoor & dir);
string coordenadas(const tCoor c); // devuelve las coordenadas de esta manera ( , )
void leeSopa(tSopa & s, string pals[]);
void resuelve(tSopa s, const string p[]);

int main()
{
	string p[20];
	tDireccion d;
	tSopa s;
	
	dirs(d);
	inicializarSopa(s);
	leeSopa(s, p);
	mostrarSopa(s);
	resuelve(s, p);

	system("pause");
	return 0;
}

void inicializarSopa(tSopa & s) {
	s.alto = 0;
	s.ancho = 0;
	for (int t = 0; t < s.alto; t++) {
		s.sopa[t] = " ";
	}
}

void mostrarSopa(tSopa const& s) {
	for (int t = 0; t < s.alto; t++) {
		cout << s.sopa[t] << endl;
	}
}

void dirs(tDireccion & dirs) {
	int t = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++){
			if (i != 0 || j != 0) { 
				dirs[t] = { i,j }; 
				t++;
			}
		}
	}
}


bool compruebaPosDir(tSopa s, string pal, tCoor pos, tCoor dir) {
	bool enc = true;
	int c = 0, i = pos.x, j = pos.y;

	while ((c < pal.length()) && enc) {
		if ((s.alto > i ) && (i>= 0) && (j >= 0) && (s.ancho > j)) {
			enc = (s.sopa[i][j] == pal[c]);
			i = i + dir.x;
			j = j + dir.y;
			c++;
			i = ((i == s.alto) && enc) ? 0 : i;
			j = ((j == s.ancho) && enc) ? 0 : j;
		}
		else { enc = false; }
	}

	return enc;
}


bool buscaDir(tSopa s, string pal, tCoor pos, tCoor & dir) {
	bool enc = false;
	int t = 0;
	tDireccion d;
	dirs(d);

	while (!enc && t < 8) {
		enc = compruebaPosDir(s, pal, pos, d[t]);
		t++;
	}

	if (enc) { dir = d[t-1]; }
	else { dir = { 0,0 }; }

	return enc;
}


bool buscaPal(tSopa s, string pal, tCoor & pos, tCoor & dir) {
	bool enc = false;
	int i = 0, j;

	while (!enc && i < s.alto) {
		j = 0;
		while (!enc && j < s.ancho) {
			enc = buscaDir(s, pal, { i, j }, dir);
			j++;
		}
		i++;
	}

	if (enc) { pos = { i - 1, j - 1}; }
	else { pos = { 0,0 }; }

	return enc;
}


void resuelve(tSopa s, const string p[]) {
	tCoor pos, dir;
	string enc; 

	for (int t = 0; t < 6; t++) {
		if (buscaPal(s, p[t], pos, dir)) { 
			cout << p[t] << " ENCONTRADA en la posicion " << coordenadas(pos) << " y direccion " << coordenadas(dir) << endl;
		}
		else { cout <<  p[t] << " NO ENCONTRADA" << endl; }
	}
}

string coordenadas(const tCoor c) {
	string p;
	p = "(" + to_string(c.x) + ", "+ to_string(c.y) + ")";
	return p;
}

void leeSopa(tSopa & s, string pals[]) {
	int i = 0, j = 0, t;
	ifstream archivo;
	archivo.open("sopa.txt");

	if (!archivo.is_open()) { cout << "No se ha podido abrir el archivo!" << endl; }
	else {
		archivo >> s.alto;
		archivo >> s.ancho;
		while (i < s.alto) {
			archivo >> s.sopa[i];
			i++;
		}
		archivo >> t;
		while (j < t) {
			archivo >> pals[j];
			j++;
		}
	}
}



