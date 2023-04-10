#include<iostream>
#include<vector>
#include<cmath>
using namespace std;


void dar_regalos(int N, int J, int M, int juguete, vector<int> const& n_edad, vector<int> const& j_edad,
	             vector<vector<int>> const& sxnxj, int & s, int & smax, int & tienenMjuguetes,
				 vector<int> & jxn) {

	for (int ninno = 0; ninno < N; ++ninno) { //si asignamos el juguete a alguien
		if (j_edad[juguete] <= n_edad[ninno]) {
			s += sxnxj[ninno][juguete]; //añadimos la satisfacción
			++jxn[ninno]; //añaidmos un juguete más a ese niño
			tienenMjuguetes = (jxn[ninno] == M) ? tienenMjuguetes + 1 : tienenMjuguetes;

			if (juguete == J - 1) {
				if (tienenMjuguetes == N && s > smax)
					smax = s;
			}
			else {
				dar_regalos(N, J, M, juguete + 1, n_edad, j_edad, sxnxj, s, smax, tienenMjuguetes, jxn);
			}

			s -= sxnxj[ninno][juguete]; //restamos la satisfacción
			tienenMjuguetes = (jxn[ninno] == M) ? tienenMjuguetes - 1 : tienenMjuguetes;
			--jxn[ninno]; //restamos un juguete a ese niño
		}
	}
	//si no asignamos el juguete a nadie
	if (juguete == J - 1) {
		if (tienenMjuguetes == N && s > smax)
			smax = s;
	}
	else {
		///if (estimacion + s > smax)
			dar_regalos(N, J, M, juguete + 1, n_edad, j_edad, sxnxj, s, smax, tienenMjuguetes, jxn);
	}
}

bool resuelveCaso() {
	int j, n, m;
	cin >> j >> n >> m;

	if (j == 0 && n == 0 && m == 0)
		return false;
	else {
		int s = 0, smax = 0, tMj = 0;
		vector<int> n_edad(n), j_edad(j), jxn(n);
		vector<vector<int>> sxnxj(n, vector<int>(j));
		for (int i = 0; i < j; ++i)
			cin >> j_edad[i];
		for (int i = 0; i < n; ++i)
			cin >> n_edad[i];
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < j; ++k)
				cin >> sxnxj[i][k];
		}

		dar_regalos(n, j, m, 0, n_edad, j_edad, sxnxj, s, smax, tMj, jxn);
		cout << smax << '\n';

		return true;
	}

}

int main() {
	while(resuelveCaso()){}
	return 0;
}