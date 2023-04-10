#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

typedef struct {
	int max;
	int min;
} info_vector;
using par = std::pair<bool, info_vector>;


par parc_ord(vector<int> const& v, int ini, int fin) {

	if (ini >= fin) {
		return { true, { v[ini] , v[ini] } };
	}
	else {
		int mitad = (ini + fin) / 2;
		par pord_d = parc_ord(v, mitad + 1, fin);
		par pord_i = parc_ord(v, ini, mitad);

		return { pord_d.first && pord_i.first && 
			(pord_d.second.max >= pord_i.second.max) && (pord_i.second.min <= pord_d.second.min),
			{ pord_d.second.max, pord_i.second.min} };
	}

}

bool parcialmenteOrdenado(vector<int> const& v) {
	return parc_ord(v, 0, v.size()-1).first;
}

bool resuelveCaso() {
	int aux;
	cin >> aux;

	if (aux == 0)
		return false;
	else {
		vector<int> v;
		while (aux != 0) {
			v.push_back(aux);
			cin >> aux;
		}
		
		if (parcialmenteOrdenado(v)) cout << "SI \n";
		else cout << "NO \n";

	}

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

/*
2 6 3 8 0
6 12 8 18 10 15 16 40 0
5 5 5 5 0
2 6 1 8 0
1 3 2 5 3 1 3 4 0
0

*/