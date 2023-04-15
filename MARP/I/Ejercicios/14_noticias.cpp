///EDURNE RUIZ DG33
/*
En una red social hay una serie de usuarios que se comunican entre
ellos dentro de una serie de grupos de amigos. Queremos analizar el
proceso de distribuci´on de noticias entre estos usuarios.
Inicialmente, alg´un usuario recibe una noticia de una fuente externa.
Entonces env´ıa la noticia a sus amigos en la red (dos usuarios son amigos
si hay al menos un grupo al que pertenezcan ambos). Los amigos env´ıan
a su vez esa noticia a sus amigos y el proceso continua as´ı hasta que no
exista una pareja de amigos tal que uno de ellos conozca la noticia y el
otro no.
Para cada usuario de la red, queremos saber cu´antos usuarios terminar´ıan conociendo la noticia si
inicialmente solamente ese usuario la conoc´ıa.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Grafo.h"
#include "TreeSet_AVL.h"
using namespace std;

class RedSocial {
	Grafo amistades;
	int usuarios, grupos;
	vector<int> conectados;
public:

	RedSocial(int u, int g) : usuarios(u), grupos(g), amistades(u), conectados(u, 0), marcados(u, -1) {
		int tam;
		while (g--) {
			cin >> tam;
			adyacentes(tam);
		}
		conectar();
	}

	//devuelve el nº de personas a las que les llega la noticia si el primer usuario en tenerla es el dado
	int reciben_noticia(int usuario) {
		return conectados[usuario];
	}

private:

	vector<int> marcados;

	//leemos todos los usuarios de un mismo grupo y los hacemos adyacentes al primero que leemos de dicho grupo
	//da igual q no los conectemos entre todos, seguirán perteneciendo a la misma componente conexa
	void adyacentes(int tam) {
		if (tam != 0) {
			vector<int> v_u(tam);

			cin >> v_u[0];
			for (int i = 1; i < tam; ++i) {
				cin >> v_u[i];
				amistades.ponArista(v_u[0] - 1, v_u[i] - 1);
			}
		}
	}

	//calculamos el nº de vértices en cada componente conexa
	//en marcados[i] se guarda el vertice "Origen" (el primero que descubrimos) de la componente conexa del vértice i
	//en conectados[i] guardamos el nº de vertices a los que esta conectado el vertice i
	void conectar() {
		for (int v = 0; v < usuarios; ++v) {
			if (marcados[v] == -1) { //si no ha sido marcado, hemos encontrado un vértice origen
				int a = 0;
				amigos_conectados(v, a, v);
				conectados[v] = a; //
			}
			else
				conectados[v] = conectados[marcados[v]]; //si ya ha sido marcado, ya hemos descubierto y calculado su comp conexa
		}
	}

	void amigos_conectados(int v, int & amigos, int componente) {
		++amigos; //pq hemos encontrado un nuevo vertice de la componente conexa
		marcados[v] = componente; //asociamos al nuevo vertice con el vertice origen de su comp conexa
		for (int w : amistades.ady(v)) {
			if (marcados[w] == -1)
				amigos_conectados(w, amigos, componente);
		}
	}
};


bool resuelveCaso() {
	int usuarios, grupos;
	cin >> usuarios >> grupos;

	if (!std::cin)
		return false;
	else {
		RedSocial rs(usuarios, grupos);
		for (int v = 0; v < usuarios; ++v) {
			cout << rs.reciben_noticia(v) << " ";
		}
		cout << "\n";
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:

7 5
3 2 5 4
0
2 1 2
1 1
2 6 7

4 2
1 1
1 3

salida:
4 4 1 4 4 2 2

1 1 1 1

*/