#include <iostream>
#include <vector>
#include <string>
using namespace std;
using par = std::pair<int, int>;

par picos_valles(vector<int> const& v) {
	int picos = 0, valles = 0, n = 1, N = v.size();

	while (n < N-1) {
		picos = (v[n - 1] < v[n] && v[n] > v[n + 1]) ? picos + 1 : picos;
		valles = (v[n - 1] > v[n] && v[n] < v[n + 1]) ? valles + 1 : valles;
		++n;
	}

	return { picos, valles };
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!std::cin)
		return false;
	else {
		vector<int> v(n);
		for (int i = 0; i < n; ++i)
			cin >> v[i];
		
		par p = picos_valles(v);
		cout << p.first << " " << p.second << '\n';
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