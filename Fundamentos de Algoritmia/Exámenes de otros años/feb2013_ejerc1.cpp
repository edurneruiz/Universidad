#include <iostream>
#include <vector>
using namespace std;


//funciones
bool resolver(vector<int> v);
bool resuelveCaso();

int main() {
	while (resuelveCaso());
	return 0;
}

bool resuelveCaso() {
	int aux = 0, i = 0, tam;
	cin >> tam;
	vector<int> v(tam);
	for (int i = 0; i < tam; i++) { cin >> v[i]; }
	
	if (resolver(v)) { cout << "Válido" << endl; }
	else { cout << "No válido" << endl; }
	return true;
}

bool resolver(vector<int> v) {
	bool si = true, cambio = false;
	int N = v.size(), i = 0;

	while ((i < N - 1) && si) {
		if (v[i] != v[i + 1] && !cambio) cambio = true;
		else if (v[i] != v[i + 1] && cambio) si = false;
		i++;
	}

	return si;
}

/*

precondición: { 0 <= n && vectorBinario(V) }
	fun resolver(V[0...n) de {0,1}) dev p : bool
postcondición: { p = cierto -> ex. i : 0 <= i < n tq (todoUnos(V,i) && todoCeros(V,i+1)) || todoUnos(V,n) || todoCeros(V,n) }

vectorBinario(V) = (pt i : 0 <= i < n : (V[i] = 0 || V[i] = 1))
todoUnos(V, k) = (pt j : 0 <= j <= k : V[j] = 1)
todoCeros(V, k) = (pt j : 0 <= j <= k : V[j] = 0)

invariante, I : { 
cota, C : n - 1 - i
				   
*/