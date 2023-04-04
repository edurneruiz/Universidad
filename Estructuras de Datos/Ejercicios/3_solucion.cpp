#include <iostream>
#include <vector>
#include <fstream>
#include "3_complejo.h"
using namespace std;


bool mandelbrot(complejo<float> & z, complejo<float> & c, const int n, int i) {
	if (i == n) return true;
	else {
		complejo<float> z_n = (z*z) + c;
		if (z_n.mod() > 2) return false;
		else return mandelbrot(z_n, c, n, i++);
	}

}

bool resuelveCaso() {
	int n, i = 0;
	complejo<float> c, z;
	cin >> c >> n;
	
	if (mandelbrot(z, c, n, i)) cout << "SI" << endl;
	else cout << "NO" << endl;

	return true;
}

int main() {
	int num_casos, i = 0;
	cin >> num_casos;
	while (i < num_casos) {
		resuelveCaso();
		i++;
	}

	system("pause");
	return 0;
}