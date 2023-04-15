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
using puntero = int*;
using matriz = vector<vector<bool>>;

class RedSocial {
	Grafo g_amistades;
	matriz m_amistades;

	int usuarios, grupos;
public:

	RedSocial(int u, int g) : usuarios(u), grupos(g), g_amistades(u), m_amistades(u, vector<bool>(u, false)), conectados(u, nullptr) {
		int tam;
		//iniPunt();
		while (g--) {
			cin >> tam;
			adyacentes(tam);
		}
	}

	int compartir_noticia(int usuario) {
		return *conectados[usuario];
	}

private:
	vector<puntero> conectados;

	void iniPunt() {
		for (int u = 0; u < usuarios; ++u) {
			int cero = 0;  puntero p = &cero;
			conectados[u] = p;
		}
	}

	//leemos todos los usuarios de un mismo grupo y los hacemos adyacentes (son contactos directos)
	void adyacentes(int tam) {
		if (tam != 0) {
			vector<int> v_u(tam); int cero = 0;

			cin >> v_u[0];

			if (conectados[v_u[0]] == nullptr)
				conectados[v_u[0]] = &cero;

			for (int i = 1; i < tam; ++i) {
				cin >> v_u[i];
				for (int w = 0; w < i; ++w) {
					if (!m_amistades[v_u[i]][v_u[w]]) {
						g_amistades.ponArista(v_u[i] - 1, v_u[w] - 1);
						m_amistades[v_u[i]][v_u[w]] = true;
						++conectados[v_u[0]];
					}
				}
				conectados[v_u[i]] = conectados[v_u[0]];
			}
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
		for (int u = 0; u < usuarios; ++u)
			cout << rs.compartir_noticia(u) << " ";
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