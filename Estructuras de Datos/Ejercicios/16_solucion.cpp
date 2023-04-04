#include <iostream>
#include <string>
#include "list2.h"
using namespace std;

using par = std::pair<int, string>;

class franjaDeEdad {
	const int _min, _max;
public:
	franjaDeEdad(int min = 0, int max = 0) : _min(min), _max(max) {}
	bool operator() (par p) {
		return (_min <= p.first) && (p.first <= _max);
	}
};

bool resuelveCaso() {
	int n, min = 0, max = 0;
	
	cin >> n >> min >> max;
	if ( n == 0 && min == 0 && max == 0) return false;
	
	list_viajeros<par, franjaDeEdad> v;
	franjaDeEdad edad(min, max);
	for (int i = 0; i < n; ++i) {
		par p;
		cin >> p.first;
		getline(cin, p.second);
		v.push_back(p);
	}
	v.remove_if(edad);
	for (auto it : v) {
		cout << it.second << "\n";
	}
	cout << "---\n";
	return true;
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}