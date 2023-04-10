/*Se dispone de una lista de n productos alimenticios entre los que se quiere escoger
algunos para seguir una dieta adecuada. Para cada producto i (0 ≤ i < n) se conoce su precio
pi ≥ 0, su contenido en proteinas qi ≥ 0 y su cantidad de calorías ci ≥ 0. Se desea seleccionar
algunos de estos productos (a lo sumo uno de cada) de forma que el precio total no supere un
presupuesto M, el contenido proteico total sea al menos de Q y el valor calórico sea lo menor
posible. Diseñar un algoritmo de vuelta atrás para encontrar la selección óptima, es decir, la
que minimiza la cantidad de calorías. Se valorarán las podas realizadas.*/
#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;

typedef struct {
	double precio;
	double proteinas;
	double calorias;
	double rendimiento;
} info_producto;

bool orden(info_producto const& p1, info_producto const& p2) {
	return (p1.rendimiento > p2.rendimiento);
}

double estimar(int n, int m, int q, int producto, vector<info_producto> const& info, 
			   int const& c, int const& presupuesto) {
	int hueco = m - presupuesto;
	int beneficio = c;
	int i = producto + 1;

	while (i < n && hueco >= info[producto].precio) {
		hueco -= info[producto].precio;
		beneficio += info[producto].calorias;
		++i;
	}
	if (i <= n - 1) //fraccionamos siguiente producto
		beneficio += hueco * info[producto].calorias;

	return beneficio;
}

void hacer_compra(int n, int m, int q, int producto, vector<info_producto> const& info,
				  int & presupuesto, int& proteinas, double & c, double & cmin) {

	//elegimos el producto correspondiente
	if (presupuesto + info[producto].precio <= m) {
		c += info[producto].calorias;
		presupuesto += info[producto].precio;
		proteinas += info[producto].proteinas;

		if (producto == n - 1) {
			if (presupuesto <= m && proteinas >= q)
				cmin = fmin(c, cmin);
		}
		else
			hacer_compra(n, m, q, producto + 1, info, presupuesto, proteinas, c, cmin);

		c -= info[producto].calorias;
		presupuesto -= info[producto].precio;
		proteinas -= info[producto].proteinas;
	}
	//no elegimos el producto
	if (producto == n - 1) {
		if (presupuesto <= m && proteinas >= q)
			cmin = fmin(c, cmin);
	}
	else {
		if (estimar(n, m, q, producto, info, c, presupuesto) < cmin) //estimamos
			hacer_compra(n, m, q, producto + 1, info, presupuesto, proteinas, c, cmin);
	}
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;
	else {
		int m, q, presupuesto = 0, proteinas = 0;
		double c = 0, cmin = INT_MAX;
		cin >> m >> q;
		vector<info_producto> productos(n);
		for (int i = 0; i < n; ++i) {
			auto & it = productos[i];
			cin >> it.precio >> it.proteinas >> it.calorias;
			it.rendimiento = (it.proteinas - it.calorias) / it.precio;
		}

		sort(productos.begin(), productos.end(), &orden); //ordenamos por mayor rendimiento
		hacer_compra(n, m, q, 0, productos, presupuesto, proteinas, c, cmin);
		if (cmin == INT_MAX)
			cout << "IMPOSIBLE \n";
		else
			cout << cmin << "\n";

		return true;
	}
}

int main() {
	while(resuelveCaso()){}
	return 0;
}

/*
3 20 20
10 10 2
15 13 1.1
10 17 1.8

-> 3.8
*/