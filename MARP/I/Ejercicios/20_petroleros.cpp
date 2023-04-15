///EDURNE RUIZ DG33
/*

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <queue>
#include "Grafo.h"
#include "TreeSet_AVL.h"
using namespace std;
using par = std::pair<int, int>;
typedef struct {
	bool cont; // 
	int mancha;
} celda;
using c_map = vector<vector<celda>>;
using b_map = vector<vector<bool>>;


class ZonaContaminada {
	c_map mapa; //en (i,j) -> si está contaminada o no, y mancha a la q pertenece en el caso de que sí
	vector<par> tam_manchas; //en posición i -> info i-ésima mancha : mancha a la q se anexiona, tamaño inicial
	int tam_mayor_mancha, num_manchas;
	int F, C;
	
public:
	
	ZonaContaminada(int fila, int col) : F(fila), C(col), mapa(fila, vector<celda>(col)), 
					tam_manchas(vector<par>(1)), tam_mayor_mancha(0), num_manchas(0) {
		char aux;
		for (int fi = 0; fi < F; ++fi) {
			for (int ci = 0; ci < C; ++ci) {
				cin >> aux;
				mapa[fi][ci] = { (aux == '#'), -1 };
			}
		}
		tam_manchas[0] = { 0, -1 };
		detectarManchasIniciales();
	}

	void nuevaZona(int f, int c) {
		if (celdaDentro(f, c)) {
			mapa[f][c].cont = true;
			detectarManchasNuevas(f, c);
		}	
	}

	int mayorMancha() {
		return tam_mayor_mancha;
	}

private:
	vector<par> direcciones = { {1,0}, {0,1}, {-1, 0}, {0, -1}, {1, -1}, {1, 1}, {-1,-1}, {-1, 1} };
	b_map visitados;

	bool celdaDentro(int f, int c) {
		return 0 <= f && f < F && 0 <=c && c < C;
	}

	bool esMancha(int f, int c) {
		return mapa[f][c].cont;
	}

	//numeramos las manchas de 1 a M
	void detectarManchasIniciales() {
		int mayor = 0, tam;
		for (int f = 0; f < F; ++f) {
			for (int c = 0; c < C; ++c) {
				if (esMancha(f, c) && !visitados[f][c]) { //entra cada vez que se descubre una nueva mancha
					++num_manchas;
					tam = 0;
					dfs(f, c, num_manchas, tam);
					tam_manchas.push_back({ num_manchas, tam });

					tam_mayor_mancha = fmax(tam_mayor_mancha, tam);
				}
			}
		}
	}

	void dfs(int f, int c, int mancha, int & tam) {
		++tam; //pq hemos encontrado una nueva zona contaminada de la mancha
		mapa[f][c].mancha = mancha; //asociamos a la nueva zona con la mancha a la q pertenece
		for (par d : direcciones) {
			int fn = f + d.first, cn = c + d.second;
			if (celdaDentro(fn, cn) && esMancha(fn, cn) && !visitados[fn][cn])
				dfs(fn, cn, mancha, tam);
		}
	}

	void detectarManchasNuevas(int f, int c) {
		vector<bool> marcadas(num_manchas, false);
		int ady = 0; //nº manchas adyacentes a la nueva zona contaminada
		int m = num_manchas + 1; //nº de la mancha a la que se va a anexionar
		
		visitados[f][c]= true;
		for (par d : direcciones) {
			int fn = f + d.first, cn = c + d.second;
			
			if (celdaDentro(fn, cn) && esMancha(fn, cn)) {
				auto a = mapa[fn][cn].mancha;

				if (!marcadas[a]) {
					m = (ady == 0) ? a : m;

					marcadas[a] = true;
					
					tam_manchas[m].second += tam_manchas[a].second;
					tam_manchas[a].first = m;
					++ady; 
				}
			}	
		}

		if (ady == 0) { // m = num_manchas + 1
			++num_manchas;
			tam_manchas.push_back({ num_manchas, 1 });
			mapa[f][c].mancha = num_manchas;
		}
		else {
			mapa[f][c].mancha = m;
			tam_mayor_mancha = fmax(tam_mayor_mancha, tam_manchas[m].second);
		}
	}

	/*void anexion(int f, int c, int min, int tam, queue<int> & m_ady) {
		if (m_ady.empty()) { //es una nueva mancha
			++num_manchas;
			tam_manchas.push_back({ num_manchas, tam });
			mapa[f][c].mancha = num_manchas;
		}
		else if (m_ady.size() == 1) { //se anexiona a una existente
			++tam_manchas[min].second; //aumenta el tamñao
			mapa[f][c].mancha = min; //la nueva zona pertenece a esa mancha
		}
		else {
			tam_manchas[min].second = tam; //tamaño de la mancha tras crecer
			while (!m_ady.empty()) {
				tam_manchas[m_ady.front()].first = min;
				m_ady.pop();
			}
		}
	}*/
};

bool resuelveCaso() {
	int f, c;
	cin >> f >> c;
		
	if (!std::cin)
		return false;
	else {
		ZonaContaminada zc(f, c);
		int n, a1, a2;
		cin >> n;

		while (n--) {
			cin >> a1 >> a2;
			zc.nuevaZona(a1, a2);
			cout << zc.mayorMancha() << '\n';
		}

		return true;
	}

}


int main() {
	while (resuelveCaso()) {}
	return 0;
}
/*
8 8
 # #   #
 ###  ##
     ###
 #
 # #
 ### ##
###  ##
  #
3
6 8
2 5
6 5

*/