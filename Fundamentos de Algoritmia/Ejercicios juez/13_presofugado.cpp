#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


char preso_fugado(vector<char> const& v, char pp, char pult, int ini, int fin) {
	if (v[ini] != pp) //falta el primero
		return pp;
	else if (v[fin] != pult) //falta el último
		return pult;
	else if (v[fin] - v[ini] == 2) { //falta el del medio
		return pp + 1;
	}
	else {
		int mitad = (ini + fin) / 2;
		if (v[fin] - v[mitad] != fin - mitad)
			return preso_fugado(v, v[mitad], pult, mitad, fin);
		else if (v[mitad] - v[ini] != mitad - ini)
			return preso_fugado(v, pp, v[mitad], ini, mitad);
	}
}

void resuelveCaso() {
	vector<char> v;
	char pp, pult, aux;
	cin >> pp >> pult;

	for (int i = 0; i < pult - pp; ++i) {
		cin >> aux;
		v.push_back(aux);
	}

	cout << preso_fugado(v, pp, pult, 0, v.size() - 1) << '\n';
}

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos) {
		resuelveCaso();
		--numCasos;
	}
	system("pause");
	return 0;
}
/*
12
a e
a b c e
c h
d e f g h
c h
c e f g h
c h
c d f g h
c h
c d e g h
c h
c d e f h
c h
c d e f g
d h
e f g h
d h
d f g h
d h
d e g h
d h
d e f h
d h
d e f g


*/