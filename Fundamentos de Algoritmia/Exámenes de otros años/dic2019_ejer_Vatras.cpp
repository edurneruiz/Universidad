#include<iostream>
#include<vector>
using namespace std;


void resolver(int N, int momento, int& dn, int& dn_max, bool& s, vector<int>& sol, vector<vector<int>>& donaciones, vector<vector<int>>& vetos, vector<bool>& repetidos, vector<int>& max_momentos, int& bf) {

	for (int artista = 0; artista < N; artista++) {
		if (((momento == 0) || (vetos[artista][sol[momento - 1]] == 1)) && !repetidos[artista]) {
			sol[momento] = artista;
			dn += donaciones[artista][momento];
			repetidos[artista] = true;
			bf -= max_momentos[momento];

			if (momento == N - 1) { 
				dn_max = (dn_max > dn) ? dn_max : dn; 
				s = true;
			}
			else {
				if (dn_max <= dn + bf) resolver(N, momento + 1, dn, dn_max, s, sol, donaciones, vetos, repetidos, max_momentos, bf);
			}

			sol[momento] = -1;
			dn -= donaciones[artista][momento];
			repetidos[artista] = false;
			bf += max_momentos[momento];

		}
	}

}

void resuelveCaso() {
	int N, dn = 0, dn_max = 0, k = 0, aux, v = 0, max = 0, beneficio_max = 0;
	bool s = false, igualAcero = true;
	cin >> N;
	vector<int> sol(N, -1), max_momento(N, 0);
	vector<vector<int>> donaciones(N), vetos(N);
	vector<bool> repetidos(N, false);
	for (int i = 0; i < N; i++) { //crear matriz de donaciones
		for (int j = 0; j < N; j++) { 
			cin >> aux;
			donaciones[i].push_back(aux);
			max_momento[j] = (max_momento[j] > aux) ? max_momento[j] : aux;
		}
	}
	for (int i = 0; i < N; i++) { //crear matriz de vetos
		for (int j = 0; j < N; j++) {
			cin >> aux;
			vetos[i].push_back(aux);
		}
		beneficio_max += max_momento[i];
	}
	
		/*igualAcero = igualAcero && (aux == 0);
	}
	if (igualAcero) {
		v++;
		sol[0] = i;
		dn_max += donaciones[i][0];
		dn += donaciones[i][0];
		repetidos[i] = true;
	}
	igualAcero = true;
}

if ((v == 0) || (v == 1)) {
	resolver(N, k + v, dn, dn_max, s, sol, donaciones, vetos, repetidos);
	if (!s) cout << "NEGOCIA CON LOS ARTISTAS" << endl;
	else cout << dn_max << endl;
}
else cout << "NEGOCIA CON LOS ARTISTAS" << endl;*/
		resolver(N, k, dn, dn_max, s, sol, donaciones, vetos, repetidos, max_momento, beneficio_max);
		if (dn_max == 0) cout << "NEGOCIAR CON LOS ARTISTAS" << endl;
		else cout << dn_max << endl;
}


int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	system("pause");
	return 0;
}
