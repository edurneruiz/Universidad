/*Se tienen dos vectores de enteros ordenados a y b con n y m elementos respectivamente. 
Se desea calcular el beneficio del vector a con respecto a b. El beneficio del vector se calcula 
sumando los beneficios obtenidos por cada uno de sus elementos. El beneficio de un elemento a[i] 
es el producto de la cantidad de elementos de b que son estrictamente menores que asi) y la cantidad 
de elementos de b que son estrictamente mayores que a[i]*/

#include<iostream>
#include<vector>
using namespace std;

void print(vector<int> const& v) {
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << "\n";
}

/*
5 8
1 2 4 6 9
2 3 4 5 6 7 8 9

3 4
2 4 6
3 5 7 9

3 4
5 6 7
8 9 10 11

3 4
6 8 9
5 6 7 8

4 3
4 6 8 9
3 5 6

5 4
10 14 25 36 78
20 30 40 50

8 8
5 18 29 36 37 42 58 60
6 19 29 31 45 49 50 59

*/


///5 18 29 36 37 42 58 60  
///6 19 29 31 45 49 50 59
vector<int> beneficio_deA_respecto_deB(int n, int m, vector<int> const& A, vector<int> const& B) {
	vector<int> C(n);
	int i = 0, j = 0;

	while (i < n && j < m) {
		if (A[i] >= B[m - 1] || A[i] <= B[0]) { //es mayor q todos los de B -> hay 0 elems en B mayores q A[i] -> C[i] = 0
			// es menor que todos los de B -> hay 0 elems en B menores q A[i] -> C[i] = 0
			C[i] = 0;
			++i;
		}
		else {
			if (A[i] == B[j]) {
				C[i] = j * (m - (j+1));
				++i; //++j 
			}
			else if (A[i] > B[j] && A[i] < B[j+1]) {
				C[i] = (j + 1)*(m - (j + 1));
				++i;
			}
			else if (A[i] > B[j])
				++j;
		}
	}

	return C;
}

bool resuelveCaso() {
	int n, m;
	cin >> n >> m;

	if (n == 0 && m == 0)
		return false;
	else {
		vector<int> A(n), B(m);
		for (int i = 0; i < n; ++i)
			cin >> A[i];
		for (int i = 0; i < m; ++i)
			cin >> B[i];

		vector<int> C = beneficio_deA_respecto_deB(n, m, A, B);
		print(C);
		return true;
	}
}

int main() {
	while(resuelveCaso()){}
	return 0;
}