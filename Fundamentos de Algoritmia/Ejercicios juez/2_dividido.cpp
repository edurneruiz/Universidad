#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool dividido(vector<int> const& v, int p) {
	int n = 0, N = v.size(); bool d = false;
	int min = v[N-1], max = v[0];
	
	if (p == 0 || p == N - 1)
		return true;
	else {
		while (n <= p) {
			max = (v[n] > max) ? v[n] : max;
			++n;
		}
		while (n < N) {
			min = (v[n] < min) ? v[n] : min;
			++n;
		}
		return max < min;
	}
}


bool resuelveCaso() {
	int n, p;
	cin >> n >> p;

	if (!std::cin)
		return false;
	else {
		vector<int> v(n);
		for (int i = 0; i < n; ++i)
			cin >> v[i];

		if (dividido(v, p)) cout << "SI \n";
		else cout << "NO \n";

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
	return 0;
}