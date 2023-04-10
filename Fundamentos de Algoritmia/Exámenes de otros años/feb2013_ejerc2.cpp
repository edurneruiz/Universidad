#include <iostream>
#include <vector>
using namespace std;

//funciones
int histograma(vector<int> v, vector<int> & hist, int n);
bool resuelveCaso();
void mostrar(vector<int> v);

int main() {
	while (resuelveCaso());
	system("pause");
	return 0;
}

bool resuelveCaso() {
	int i = 0, tam;
	cin >> tam;
	vector<int> v(tam), h(tam);

	for (int i = 0; i < tam; i++) { cin >> v[i]; }
	histograma(v, h, tam - 1);
	mostrar(h);
	return true;
}

int histograma(vector<int> v, vector<int> & hist, int n) {
	
	if (n == 0) hist[n] = v[n];
	else { hist[n] = histograma(v, hist, n - 1) + v[n]; }

	return hist[n];
}

void mostrar(vector<int> v) {
	for (int i = 0; i < v.size(); i++) { cout << v[i] << " "; }
}