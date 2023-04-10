#include <iostream>
#include <vector>
using namespace std;


/*
vector tira: representación de la tira de colores
en el vector l_repes: en la posición i-ésima se guarda el nº de veces q aparece el color i 
en el vector l_seguidas: en la posición i-ésima se guarda si el color i aparece dos veces seguidas
*/
void combinaciones_luces(int & sol, vector<int> & l_repes, int & consumo, int nivel, int lng, 
						int nCol, int maxConsumo, vector<int> const& consumo_luces, int ant, int ant2) {
	for (int color = 0; color < nCol; ++color) {
		if (nivel <= 2 || !(color == ant && color == ant2)) { //si no aparece ya dos veces seguidas dicho color
			//marcar q vas a usar otra vez ese color: nº utilizado y consumo
			++l_repes[color];
			consumo += consumo_luces[color];

			if (consumo <= maxConsumo) {
				if (l_repes[color] <= 2 + nivel - l_repes[color]) {
					if (nivel == lng - 1)
						++sol;
					else
						combinaciones_luces(sol, l_repes, consumo, nivel + 1, lng, nCol, maxConsumo, consumo_luces, color, ant);
				}
			}
			//desmarcar
			--l_repes[color];
			consumo -= consumo_luces[color];
		}
	}
}

bool resuelveCaso() {
	int lng, nCol, maxConsumo;
	cin >> lng;

	if (lng == 0)
		return false;
	else {
		cin >> nCol >> maxConsumo;
		vector<int> tira(lng, -1), consumo_luces(nCol), luces_repes(nCol, 0);
		vector<bool> luces_seguidas(nCol, false);
		int sol = 0, nivel = 0, consumo = 0;
		for (int i = 0; i < nCol; ++i) {
			cin >> consumo_luces[i];
		}
		combinaciones_luces(sol, luces_repes,consumo, nivel, lng, nCol, maxConsumo, consumo_luces, 0,0);
		cout << sol << '\n';
	}
	return true;
}

int main() {
	while (resuelveCaso()){}
	return 0;
}