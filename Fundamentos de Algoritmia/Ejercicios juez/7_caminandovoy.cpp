#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
using par = std::pair<bool, int>;

bool apta(vector<int> const& v, int D) {
	int n = 0, N = v.size(), dact = 0, dmax = 0;

	while (n < N - 1) {
		if (v[n] < v[n + 1])
			dact += (v[n+1] - v[n]);
		else
			dact = 0;

		dmax = fmax(dmax, dact);
		++n;
	}

	return dmax <= D;
}

bool resuelveCaso() {
	int pendiente_maxima, N, aux;
	cin >> pendiente_maxima;
	if (!std::cin)
		return false;
	else {
		cin >> N;
		vector<int> v(N);
		for (int i = 0; i < N; ++i) {
			cin >> aux;
			v[i] = aux;
		}

		if (apta(v, pendiente_maxima)) cout << "APTA \n";
		else cout << "NO APTA \n";

		return true;
	}
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

/*
300 11
1200 1250 1350 1400 1300 1600 1600 1600 1700 1500 1300
300 10
1200 1250 1350 1400 1550 1550 1550 1700 1500 1300
0 4
10 10 10 10

*/