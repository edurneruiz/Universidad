#include <iostream>
#include "stack_eda.h"
#include <string>
#include <vector>
using namespace std;

using accidente = std::pair<int, string>;


void comentario(vector<accidente> const& a) {
	stack<accidente> grave;

	for (int i = 0; i < a.size(); ++i) {
		if (grave.empty()) cout << "NO HAY \n";
		else {
			if (grave.top().first > a[i].first) {
				cout << grave.top().second << "\n";
			}
			else {
				while (!grave.empty() && grave.top().first < a[i].first)
					grave.pop();

				if (grave.empty()) cout << "NO HAY \n";
				else cout << grave.top().second << "\n";
			}
		}
		grave.push(a[i]);
	}
	cout << "--- \n";
}

bool resuelveCaso() {
	int n;

	cin >> n;
	if (!std::cin) return false;

	vector<accidente> a;
	int muertos;
	string f;
	for (int i = 0; i < n; ++i) {
		cin >> f >> muertos;
		a.push_back({ muertos, f });
	}
	comentario(a);
	return true;
}

int main() {
	while (resuelveCaso()){}
	return 0;
}