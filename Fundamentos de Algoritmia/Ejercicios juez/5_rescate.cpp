#include <iostream>
#include <vector>
#include <string>
using namespace std;
using par = std::pair<int, int>;

par rescate(vector<int> const& v, int alt) {
	int p = 0, n = 0, l = 0;
	int a = 0, b = 0, N = v.size(), l_max = 0;

	while (n < N) {
		if (v[n] > alt) {
			++l;
			++n;
		}
		else {
			if (l_max < l) {
				a = p; b = n-1; l_max = l;
			}
			++n;
			p = n;
			l = 0;
		}
	}

	return { a,b };
}

bool resuelveCaso() {
	int n, alt;
	cin >> n >> alt;
	if (!std::cin)
		return false;
	else {
		vector<int> v(n);
		for (int i = 0; i < n; ++i)
			cin >> v[i];

		par p = rescate(v, alt);
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

/*
2
10 5
3 6 4 8 9 8 7 2 8 9
7 5
8 8 8 2 3 9 9

*/