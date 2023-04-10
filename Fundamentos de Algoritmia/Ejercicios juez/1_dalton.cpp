#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool dalton(vector<int> const& v) {
	bool id = true, di = true; int n = 0, N = v.size();

	while (n < N - 1) {
		id = id && (v[n] < v[n + 1]);
		di = di && (v[n + 1] < v[n]);
		++n;
	}

	return id || di;
}


bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;
	else {
		vector<int> v(n);
		for (int i = 0; i < n; ++i)
			cin >> v[i];
		
		if (dalton(v)) cout << "DALTON \n";
		else cout << "DESCONOCIDOS \n";

		return true;
	}
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}