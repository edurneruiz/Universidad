#include "plantacion.h"


//prototipos 
void inicializar(tPlantacion & plantacion);
void mostrarPlantacion(tPlantacion const& plantacion);



void inicializar(tPlantacion & plantacion) {
	plantacion.id = " ";
	plantacion.num_f = 0;
	plantacion.num_col = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) { plantacion.arboles[i][j] = 0; }
	}
}

bool cargarPlantacion(tPlantacion & plantacion, string f) {
	bool carga;
	int i = 0, j;
	ifstream archivo;
	archivo.open(f);

	inicializar(plantacion);
	if (!archivo.is_open()) { carga = false; }
	else {
		archivo >> plantacion.id;
		archivo >> plantacion.num_f;
		archivo >> plantacion.num_col;
		while (i < plantacion.num_f) {
			j = 0;
			while (j < plantacion.num_col) {
				archivo >> plantacion.arboles[i][j];
				j++;
			}
			i++;
		}
		carga = true;
	}
	archivo.close();
	return carga;
}

void mostrarPlantacion(tPlantacion const& plantacion) {
	for (int i = 0; i < plantacion.num_f; i++) {
		for (int j = 0; j < plantacion.num_col; j++) { 
			cout << plantacion.arboles[i][j] << " "; 
		}
		cout << endl;
	}
}

int calcularPlatanosParcela(tPlantacion const& plantacion, int fila, int col, int lado) {
	int i = fila, j, platanos = 0;

	while ((i < plantacion.num_f) && (i < fila + lado)) {
		j = col;
		while ((j < plantacion.num_col) && (j < col + lado)) {
			platanos += plantacion.arboles[i][j];
			j++;
		}
		i++;
	}
	return platanos;
}

string devolverId(tPlantacion const& plantacion) {
	return plantacion.id;
}

int devolverFilas(tPlantacion const& plantacion) {
	return plantacion.num_f;
}
int devolverColumnas(tPlantacion const& plantacion) {
	return plantacion.num_col;
}
