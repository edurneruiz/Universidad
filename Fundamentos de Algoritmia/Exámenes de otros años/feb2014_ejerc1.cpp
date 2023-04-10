/*
precondición: { m >= 0 && v = V && s = (sumatorio i : 0 <= i < m : v[i]) }
maximo(V[0...N) de ent, lng, m, s : ent) dev max : ent
postcondición: { max = (max p,q : 0 <= p < q < n && diferencia(m,p,q) : S(p,q)) && n = N }

diferencia(m,p,q) = (q - p = m)
S(p,q) = (sumatorio i : p <= i <= q : V[i])

Invariante: max = (max p,q : 0 <= p < q < n && diferencia(m,p,q) : S(p,q))
Condición bucle: n != N
Avanzar: n = n + 1
Cota: N - n

*/

#include <iostream>
#include <vector>
using namespace std;

int resolver(int lng, int m, int s, vector<int>& v) {
	int max = s, i = 1;

	while (i < lng - m) {
		s = s - v[i - 1] + v[m + i -1]; //suma desde p = i, q = m + i - 1
		max = (max > s) ? max : s; //restablecer
		i++; //avanzar
	}

	return max;
}

bool resuelveCaso() {
	int lng, m, s = 0, aux;

	cin >> lng >> m;
	if (lng == 0) return false;
	vector<int> vec(lng);

	for (int i = 0; i < lng; i++) { 
		cin >> vec[i]; 
		if (i < m) s += vec[i];
	}
	cout << resolver(lng, m, s, vec) << endl;
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}