#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

typedef struct {
	bool si;
	int generaciones;
} tPar;


//funciones
tPar esGenealogico(bintree<int>& a);

bool resuelveCaso() {

	if (!std::cin) return false;
	bintree<int> arbol = leerArbol(-1);
	tPar p = esGenealogico(arbol);
	if (p.si) cout << "SI " << p.generaciones << '\n';
	else cout << "NO\n";

	return true;
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos != 0) {
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}

tPar esGenealogico(bintree<int>& a) {

	if (a.empty()) return { true, 0 };
	else {
		bintree<int> izq = a.left();
		bintree<int> dcho = a.right();

		if (izq.empty() && dcho.empty()) return { true, 1 }; //si es el árbol hoja, si es genealógico y con una sola generación
		else {
			tPar p = { false, 0 };
			tPar p_iz = esGenealogico(izq);
			tPar p_d = esGenealogico(dcho);

			if (p_iz.si && p_d.si) {
				bool m_iz = (izq.empty()) ? true : (a.root() - 18 >= izq.root()); //el padre supera en al menos 18 años al hijo izq
				bool m_d = (dcho.empty()) ? true : (a.root() - 18 >= dcho.root());//el padre supera en al menos 18 años al hijo dcho
				bool h = (izq.empty()) ? false : (dcho.empty()) ? true : izq.root() - 2 >= dcho.root(); //el hijo dcho es al menos dos años menos que el hijo izq
				p.si = m_iz && m_d && h;
				p.generaciones = (p_iz.generaciones > p_d.generaciones) ? p_iz.generaciones + 1 : p_d.generaciones + 1;
				return p;
			}
			else return p;
		}
		

	}
	


}