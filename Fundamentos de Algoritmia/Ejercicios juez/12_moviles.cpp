#include <iostream>
#include <vector>
using namespace std;
using par = std::pair<bool, int>;

par movil_equilibrado() {
	int pi, di, pd, dd;
	cin >> pi >> di >> pd >> dd;

	if (pi != 0 && pd != 0) //no tiene submoviles
		return { (pi*di == pd * dd), pi + pd };
	else {
		par izq, dcho;
		if (pi == 0) izq = movil_equilibrado();
		else izq = { true, pi };
		if (pd == 0) dcho = movil_equilibrado();
		else dcho = { true, pd };

		return { dcho.first && izq.first && (izq.second * di == dcho.second * dd), 
			izq.second + dcho.second };

	}
}

void resuelveCaso() {
	if (movil_equilibrado().first) cout << "SI \n";
	else cout << "NO \n";
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
2
0 2 0 4
0 3 0 1
1 1 1 1
2 4 4 2
1 6 3 2
0 1 3 4
2 3 3 2

*/