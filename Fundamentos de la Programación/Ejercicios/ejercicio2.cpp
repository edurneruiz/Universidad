#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

const int NUM_LETRAS = 26;
const char L = 'L';

typedef struct {
	char letra;
	int frec;
} tLetra;
typedef tLetra tAbecedario[NUM_LETRAS];
typedef struct {
	tAbecedario abec;
	int cont;
} tFrase;

//prototipos funciones
void inicializarAbecedario(tFrase & frase);
bool estaEnAbecedario(tFrase & frase, char c);
void mostrarFrecuencias(tFrase & frase);

int main() {
	int longitud;
	char c;
	bool enc;
	string cadena;
	tFrase frase;
	cout << "Introduzca cadena de caracteres: ";
	getline(cin, cadena);
	while (cadena != "XXX") {
		inicializarAbecedario(frase);
		longitud = cadena.length();
		for (int i = 0; i < longitud; i++) {
			c = tolower(cadena[i]);
			if (isalpha(c)) {
				enc = estaEnAbecedario(frase, c);
				if (!enc) {
					frase.abec[frase.cont].letra = c;
					frase.abec[frase.cont].frec++;
					frase.cont++;
				}
			}
		}
		mostrarFrecuencias(frase);
		cout << "Introduzca cadena de caracteres: ";
		getline(cin, cadena);
	}
	system("pause");
	return 0;
}

void inicializarAbecedario(tFrase & frase) {
	for (int i = 0; i < NUM_LETRAS; i++) {
		frase.abec[i].frec = 0;
		frase.abec[i].letra = ' ';
	}
	frase.cont = 0;
}

bool estaEnAbecedario(tFrase & frase, char c) {
	int j = 0;
	bool encontrado = false;
	while ((j < NUM_LETRAS) && (!encontrado)) {
		encontrado = (frase.abec[j].letra == c) ? true : false;
		if (encontrado) {
			frase.abec[j].frec++;
		}
		j++;
	}
	return encontrado; 
}

void mostrarFrecuencias(tFrase & frase) {
	cout << endl;
	for (int i = 0; i < frase.cont; i++) {
		cout << "La letra '" << frase.abec[i].letra << "' aparece " << frase.abec[i].frec << " veces." << endl;
	}
	cout << endl;
}