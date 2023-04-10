#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
using superint = long long int;


superint longitud(superint n) {
	if (n == 0)
		return 0;
	else
		return 2 * longitud(n - 1) + (n + 2);
}

char letra(superint n, superint letra, superint lgt) {
	
}

bool resuelveCaso() {
	superint n, l;
	cin >> n >> l;
	
	if (!std::cin)
		return false;
	else
		cout << letra(n, l, longitud(n)) << '\n';

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}