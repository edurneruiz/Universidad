#include <iostream>
#include <vector>
#include <string>
using namespace std;
using entero = unsigned long long int;

vector<entero> tras_extremas(vector<entero> const& v) {
	entero nmin = 0, nmax = 0, min = v[0], max = v[0], n = 0, N = v.size();

	while (n < N) {
		if (v[n] == min)
			++nmin;
		if (v[n] == max)
			++nmax;

		if (v[n] < min) {
			min = v[n]; nmin = 1;
		}
		if (v[n] > max) {
			max = v[n]; nmax = 1;
		}
		
		++n;
	}
	
	return { min, nmin, max, nmax };
}

bool resuelveCaso() {
	entero aux;
	cin >> aux;
	if (!std::cin)
		return false;
	else {
		vector<entero> v, tras; 
		v.push_back(aux);
		cin >> aux;
		while (aux != 0) {
			v.push_back(aux);
			cin >> aux;
		}
		tras = tras_extremas(v);
		cout << tras[0] << " " << tras[1] << " " << tras[2] << " " << tras[3] << '\n';

		return true;
	}
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