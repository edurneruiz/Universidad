/*Edurne Ruiz, 

Precondición: { 0 <= n <= 1000 }
	func resolver(V[0...n) de ent, N : nat) dev l : ent
Postcondición: { l = (max p,q : 0 <= p < q < n && decreciente(V, p, q) : longitud(p,q)) && n = N }

Invariante : { l = (max p,q : 0 <= p < q < n && decreciente(V, p, q) : longitud(p,q)) }
Condición bucle : n != N
Cota : N - n

decreciente(V, a, b) = (p.t i : a <= i < b: V[i] >= V[i+1])
longitud(a,b) = b - a + 1

Coste = N - 1
*/
#include <iostream>
#include <vector>
using namespace std;

int resolver(int N, vector<int> a) {
	int l = 0, l_max = 1, n = 0;

	while (n < N - 1) {
		if (a[n] >= a[n + 1]) { 
			l++; 
			l_max = (l_max > l + 1) ? l_max : l + 1; //restablecer
		}
		else { l = 0; }
		n++;
	}
	return l_max;
}

void resuelveCaso() {
	int N;
	cin >> N;
	vector<int> alt(N);
	for (int i = 0; i < N; i++) { cin >> alt[i]; }
	cout << resolver(N, alt) << endl;
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	system("pause");
	return 0;
}