#include "listaDias.h"



int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	tListaDias d;

	if (!carga(d)) { cout << "No se ha podido cargar el archivo!" << endl; }
	else { muestra(d); }

	destruye(d);

	system("pause");
	return 0;
}