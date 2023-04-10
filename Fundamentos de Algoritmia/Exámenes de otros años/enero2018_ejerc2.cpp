#include<iostream>
#include<vector>
using namespace std;

void resolver(int N, int x, vector<int>& v, int ini, int fin, int&cercano) {
	
	if (v.size() == 0) cercano = 0;
	else if (ini > fin && ini == 0) cercano = v[ini];
	else if (ini > fin) cercano = v[ini - 1];
	else {
		int mitad = (ini + fin) / 2;
		if (x == v[mitad]) cercano = v[mitad];
		else if (x < v[mitad]) resolver(N, x, v, ini, mitad - 1, cercano);
		else resolver(N, x, v, mitad + 1, fin, cercano);
	}

}

void resuelveCaso() {
	int N, x, sol;
	cin >> x >> N;
	vector<int> sec(N);
	for (int i = 0; i < N; i++) { cin >> sec[i]; }
	resolver(N, x, sec, 0, N-1, sol);
	cout << sol << endl;
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	system("pause");
	return 0;
}