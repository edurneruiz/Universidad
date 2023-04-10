/*Edurne Ruiz

precondición: { N > 0 }
func resolver(V[0...n) de ent, N : nat) dev m : ent
postcondición: { m = (max p,q : 0 <= p < q < n && menores(p,q) : longitud(p,q)) && n = N }

Invariante: { m = (max p,q : 0 <= p < q < n && menores(p,q) : longitud(p,q)) }
Cota: N - n

menores(p,q) = (p.t i : p <= i <= q : V[i] < V[p-1])
longitud(p,q) = p - q + 1
*/
#include<iostream>
#include<vector>
using namespace std;

int resolver(int N, vector<int> a) {
	int max = a[0], m = 0, n = 1, m_max = 0; 

	while (n < N) {
		if (a[n] > max) { // cuando encontramos un nuevo máximo
			max = a[n]; 
			m = 0; 
		}
		else { // es menor que el máximo --> pertenece al tramo donde no mejora marca
			m++; 
			m_max = (m_max > m) ? m_max : m; //restablecer
		}
		n++;
	}
	return m_max;
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
	return 0;
}