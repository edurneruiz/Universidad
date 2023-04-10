#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


void polidivisibles(int N, int lngN, int d, vector<int> & poli) {
	if (lngN == d)
		poli.push_back(N);
	else {
		vector<int> v; v.push_back(N);
		for (int i = 0; i <= 9; ++i) {
			if ((N*10 + i) % (lngN + i) == 0)
				polidivisibles(N * 10 + i, lngN + 1, d, poli);
		}
	}
}

int longitud(int n) {
	int lng = 1;
	long long int m = n;

	while (m / 10 > 0) {
		m = m / 10;
		lng++;
	}

	return lng;
}

bool resuelveCaso() {
	int n, d;
	cin >> n >> d;

	if (!std::cin)
		return false;
	else {
		vector<int> v;
		int lngn = longitud(n);
		polidivisibles(n, lngn, d, v);
		for (int i = 0; i < v.size(); ++i)
			cout << v[i] << '\n';
	}
	cout << "--- \n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}