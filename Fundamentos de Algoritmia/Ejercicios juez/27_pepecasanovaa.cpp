#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
typedef struct {
	int duracion;
	int puntuacion;
	double rendimiento;
} tCancion;

bool orden(tCancion const& c1, tCancion const& c2) {
	return c1.rendimiento > c2.rendimiento;
}

double estimar(int n, int cancion, int duracion, vector<tCancion> const& c_info, int const& p,
			   int const& dA, int const& dB) {
	
	int hueco = 2*duracion - dA - dB, j = cancion + 1;
	double estimacion = p;

	while (j < n && c_info[j].duracion <= hueco) {
		hueco -= c_info[j].duracion;
		estimacion += c_info[j].puntuacion;
		++j;
	}
	if (j <= n - 1) //quedan canciones -> fraccionamos la siguiente
		estimacion += hueco * c_info[j].rendimiento;

	return estimacion;
}

void elegir_canciones(int n, int cancion, int duracion, vector<tCancion> const& c_info, int & p, int & pmax,
					  int dA, int dB) {
	
	if (c_info[cancion].duracion <= duracion - dA) { //añadimos la canción a la cara A
		p += c_info[cancion].puntuacion;

		if (cancion == n - 1)
			pmax = fmax(p, pmax);
		else
			elegir_canciones(n, cancion + 1, duracion, c_info, p, pmax, dA + c_info[cancion].duracion, dB);
		
		p -= c_info[cancion].puntuacion;
	}

	if (c_info[cancion].duracion <= duracion - dB) { //añadimos la canción a la cara B
		p += c_info[cancion].puntuacion;

		if (cancion == n - 1)
			pmax = fmax(p, pmax);
		else
			elegir_canciones(n, cancion + 1, duracion, c_info, p, pmax, dA, dB + c_info[cancion].duracion);

		p -= c_info[cancion].puntuacion;
	}

	if (cancion == n - 1)
		pmax = fmax(p, pmax);
	else {
		if (estimar(n, cancion, duracion, c_info, p, dA, dB) > pmax)
			elegir_canciones(n, cancion + 1, duracion, c_info, p, pmax, dA, dB);
	}

}


bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;
	else {
		int d, min = 0, p = 0, pmax = 0;
		vector<tCancion> canciones(n);
		cin >> d;
		for (int i = 0; i < n; ++i) {
			cin >> canciones[i].duracion >> canciones[i].puntuacion;
			canciones[i].rendimiento = (canciones[i].puntuacion + 0.0) / canciones[i].duracion;
		}
		sort(canciones.begin(), canciones.end(), &orden);

		elegir_canciones(n, 0, d, canciones, p, pmax, 0, 0);
		cout << pmax << '\n';

		return true;
	}
}

int main() {
	while(resuelveCaso()) {}
	return 0;
}