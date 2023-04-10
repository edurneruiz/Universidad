#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
using par = std::pair<bool, int>;

int avituallamiento(vector<int> const& v) {
	int lg = 0, lg_max = 0, n = 0, N = v.size();

	while (n < N - 1) {
		if (v[n] == v[n+1])
			++lg;
		else
			lg = 0;

		lg_max = fmax(lg, lg_max);
		++n;
	}

	return { lg_max };
}

bool resuelveCaso() {
	int aux;
	cin >> aux;
	if (aux == -1)
		return false;
	else {
		vector<int> v;
		while (aux != -1) {
			v.push_back(aux);
			cin >> aux;
		}

		int av = avituallamiento(v);
		if (av == 0) cout << "HOY NO COMEN \n";
		else cout << av << '\n';

		return true;
	}
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}

/*
0 50 50 50 100 -1
10 10 -1
0 5 -1
0 50 50 100 100 -1
0 50 50 3 3 3 -1
-1

*/