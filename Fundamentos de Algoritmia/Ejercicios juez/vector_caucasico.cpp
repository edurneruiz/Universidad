/*Un vector de enteros mayores que 0 de longitud 2^n (donde n es un número natural)
es caucásico si el valor absoluto de la diferencia entre el número de elementos pares de sus
mitades es, a lo sumo, 2 y cada mitad también es caucásica.*/
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

typedef struct {
	bool caucasico;
	int elems_par;
} info_vector;

info_vector es_caucasico(int ini, int fin, vector<int> const& v) {
	if (ini == fin)
		return { true, (v[ini] % 2 == 0) ? 1 : 0 };
	else {
		int mitad = (ini + fin) / 2;
		info_vector izq = es_caucasico(ini, mitad, v), dcho = es_caucasico(mitad + 1, fin, v);

		return { izq.caucasico && dcho.caucasico && abs(izq.elems_par - dcho.elems_par) <= 2,
				izq.elems_par + dcho.elems_par };
	}
}

bool caucasico(vector<int> const& v) {
	return es_caucasico(0, v.size() - 1, v).caucasico;
}

void resuelveCaso() {
	int N;
	cin >> N;
	vector<int> v(N);
	for (int i = 0; i < N; ++i) {
		cin >> v[i];
	}

	if (caucasico(v))
		cout << "SI" << "\n";
	else
		cout << "NO" << "\n";
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos) {
		resuelveCaso();
		--numCasos;
	}
	return 0;
}

/*
8 
2 4 6 8 1 3 5 7 
8
2 4 6 8 2 8 5 10 
16
2 4 8 12 3 7 9 21 10 20 30 1 3 5 7 40 

-> No es caucásico, porque su primera mitad tiene 4 elementos pares y
la segunda 0.
-> Es caucásico.
-> No caucásico
*/