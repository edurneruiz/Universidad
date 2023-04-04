#include "listaPeliculas.h"
#include "checkML.h"
using namespace std;

//prototipos


int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tPeliculasTotal p, act, gen, val;
	string actor;
	
	cargar(p);
	mostrar(p);

	cout << "Introduzca el nombre del actor deseado: ";
	getline(cin, actor);

	act = filtrarPorActor(p, actor);
	gen = ordenarPorGenero(act);
	mostrar(gen);

	destruir(p);

	system("pause");
	return 0;
}