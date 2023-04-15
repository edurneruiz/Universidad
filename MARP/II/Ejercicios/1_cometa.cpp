#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

typedef struct {
	int lg;
	double precio;
} tCordel;

typedef struct {
	bool posible; 
	int64_t maneras; //numero de subconjutos cuya suma sea C
	double subcjtos; //cardinal minimo de los subconjutnos cuya suma sea C
	double gasto; //gasto mínimo de los subconjuntos cuya suma sea C
} tSolucion;

void rellenoTabla(int n, int L, vector<tCordel> const& cordeles, vector<tSolucion> & s) {
	s[0] = { true, 1, 0 , 0 };
	for (int i = 1; i <= n; ++i) {
		for (int j = L; j >= cordeles[i].lg; --j) {
			s[j] = { s[j].posible || s[j - cordeles[i].lg].posible,
					s[j].maneras + s[j - cordeles[i].lg].maneras,
					fmin(s[j].subcjtos, s[j - cordeles[i].lg].subcjtos + 1),
					fmin(s[j].gasto, s[j - cordeles[i].lg].gasto + cordeles[i].precio) };
		}
	}
}

bool resuelveCaso() {
	int n, L; cin >> n >> L;
	
	if (!std::cin)
		return false;

	vector<tCordel> cordeles(n+1);
	for (int i = 1; i <= n; ++i)
		cin >> cordeles[i].lg >> cordeles[i].precio;
	
	vector<tSolucion> s(L+1, { false, 0, INT_MAX, INT_MAX });
	rellenoTabla(n, L, cordeles, s);

	if (!s[L].posible)
		cout << "NO \n";
	else
		cout << "SI " << s[L].maneras << " " << s[L].subcjtos << " " << s[L].gasto << '\n';
		
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()){}
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

/*
entrada:

4 50
10 25
20 15
30 40
40 75

3 10
1 30
2 60
3 90

3 2
1 10
1 10
1 10
salida:
SI 2 2 55
NO
SI 3 2 20
*/

