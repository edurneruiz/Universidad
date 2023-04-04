#include<iostream>
#include <string>
#include"nueva_deque.h"
using namespace std;

bool resuelveCaso() {
	int n, tmp;
	
	cin >> n;
	if (!std::cin) return false;
	
	dcola<int> d;
	for (int i = 0; i < n; ++i) {
		cin >> tmp;
		d.push_back(tmp);
	}
	d.estremecer();
	d.print();
	cout << "---\n";

	return true;
}

int main() {
	while (resuelveCaso()){}
	return 0;
}