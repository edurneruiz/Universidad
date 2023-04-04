#include <iostream>
#include <string>
#include <fstream>
#include "cola.h"
using namespace std;

bool resuelveCaso() {
	int aux;
	queue<int> q;

	cin >> aux;
	while (aux != 0) { //leer los datos
		q.push(aux);
		cin >> aux;
	}
	q.duplica();
	q.print();
	

	if (!std::cin) return false;	
	return true;
}

int main() {
	while (resuelveCaso()) {}
	system("pause");
	return 0;
}