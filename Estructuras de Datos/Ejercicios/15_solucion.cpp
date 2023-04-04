#include <iostream>
#include <string>
#include <fstream>
#include "queue_eda.h"
#include "stack_eda.h"
#include "deque_eda.h"
using namespace std;

//funciones
void print(deque<int>& may);
void paraPresidente(deque<int>& dinero, deque<int>& presi, int m, int k);
void determinarMax(int& max, int n, int df, int mt, int comensales); //df = dinero.front() ; mt = maximos.top()

bool resuelveCaso() {
	int nSobres, nComensales, aux;
	cin >> nSobres >> nComensales;

	if (nSobres == 0 && nComensales == 0) return false;

	deque<int> dinero, presi;
	for (int i = 0; i < nSobres; ++i) {
		cin >> aux;
		dinero.push_back(aux);
	}
	paraPresidente(dinero, presi, nSobres, nComensales);
	print(presi);

	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}


void print(deque<int>& may) {
	while (!may.empty()) {
		cout << may.front() << " ";
		may.pop_front();
	}
	cout << '\n';
}

void forPresidente(deque<int>& dinero, deque<int>& presi, int sobres, int comensales) {

}

void paraPresidente(deque<int>& dinero, deque<int>& presi, int sobres, int comensales) {
	int n = 1, max = 0;
	stack<int> m;

	if (!m.empty() && dinero.front() > m.top()) m.pop();
	m.push(dinero.front());
	dinero.pop_front();
	while (!dinero.empty()) {
		determinarMax(max, n, dinero.front(), m.top(), comensales);
		presi.push_back(max);
		if (!m.empty() && dinero.front() > m.top()) m.pop();
		m.push(dinero.front());
		dinero.pop_front();
	}

}

void determinarMax(int& max, int n, int df, int mt, int comensales) { //df = dinero.front() ; mt = maximos.top()
	if (n == comensales) {
		max = mt;
		n = 1;
	}
	else {
		if (max > df) ++n;
		else max = df;
	}
}