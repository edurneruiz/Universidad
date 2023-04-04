#include "listaIngredientes.h"
#include "componente.h"
#include "receta.h"


//prototipos
int menu();

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int opc;
	tListaIngredientes i;
	tComponente comp;
	tReceta r;

	if (!carga(i)) { cout << "No se hapodido cargar el archivo! " << endl; }
	else {
		r = crear();
		opc = menu();
		while (opc != 0) {
			switch (opc) {
			case 1:{
				comp = leeComponente(i);
				if (!insertar(r, comp)) { cout << "No se pueden añadir mas componentes! " << endl; }
			}
			break;
			case 2: {muestra(r); }
				   break;
			default: { cout << "Opcion no valida!" << endl; }
			}
			cout << endl;
			opc = menu();

		}
	}

	eliminar(r);
	eliminar(i);

	system("pause");
	return 0;
}

int menu() {
	int opc;

	cout << "***************" << endl;
	cout << "1- Añadir ingrediente a la receta" << endl;
	cout << "2- Mostrar estado actual de la receta" << endl;
	cout << "3- Salir" << endl;
	cout << "Opcion: ";
	cin >> opc; 
	cout << "***************" << endl;
	cout << endl;

	return opc;
}