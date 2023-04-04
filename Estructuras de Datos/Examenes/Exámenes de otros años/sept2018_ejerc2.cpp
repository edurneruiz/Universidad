#include<iostream>
#include "stack_eda.h"
#include "queue_eda.h"
using namespace std;


void print(queue<int> & cola) {
	while (!cola.empty()) {
		cout << cola.front() << " ";
		cola.pop();
	}
	cout << "\n";
}

void reordenar(queue<int> & cola) {
	stack<int> negativos;
	queue<int> positivos;

	while (!cola.empty()) {
		if (cola.front() < 0)
			negativos.push(cola.front());
		else
			positivos.push(cola.front());
		cola.pop();
	}
	while (!negativos.empty()) {
		cola.push(negativos.top());
		negativos.pop();
	}
	while (!positivos.empty()) {
		cola.push(positivos.front());
		positivos.pop();
	}
}

bool resuelveCaso() {
	int n, aux;
	cin >> n;
	if (n == 0) return false;

	queue<int> cola;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		cola.push(aux);
	}
	reordenar(cola);
	print(cola);
	cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}