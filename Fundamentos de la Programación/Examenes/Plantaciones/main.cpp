#include "plantacion.h"
#include "checkML.h"
#include "parcelas.h"
#include "cuadrillas.h"
#include <iomanip>
using namespace std;

//prototipos



int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int lado, pos = 0;
	string p1, p2;
	tPlantacion plantacion1, plantacion2;
	tParcelasTotal parcelas1, parcelas2, mezcla;
	tCuadrillasTotal cuadrillas;
	
	cout << "Introduzca la longitud del lado de las parcelas a crear: ";
	cin >> lado;
	cout << "Nombre del fichero de la primera plantacion: ";
	cin >> p1;
	cout << "Nombre del fichero de la segunda plantacion: ";
	cin >> p2;

	if (!cargarPlantacion(plantacion1, p1)) { cout << "No se ha podido cargar la primera plantacion!" << endl; }
	else {
		if (!cargarPlantacion(plantacion2, p2)) { cout << "No se ha podido cargar la segunda plantacion! " << endl; }
		else {
			cuadrillas = crearListaCuadrillas();
			parcelas1 = crearParcelas(plantacion1, lado);
			parcelas2 = crearParcelas(plantacion2, lado);

			mezcla = mezclar(parcelas1, parcelas2);
			cout << left << setw(15) << "PLANTACION" << setw(15) << "PARCELA " << "PLATANOS A RECOGER" << endl;
			mostrarListaParcelas(mezcla, pos);
			cout << endl;

			asignarParcelas(mezcla, cuadrillas);
			mostrarAsignaciones(cuadrillas);

		}
	}

	if (!escribirCuadrillas(cuadrillas)) { cout << "No se ha podido escribir en el archivo! " << endl; }
	else { cout << "Se ha escrito con exito en el archivo!" << endl; }
	
	liberar(mezcla);
	liberar(cuadrillas);

	system("pause");
	return 0;
}