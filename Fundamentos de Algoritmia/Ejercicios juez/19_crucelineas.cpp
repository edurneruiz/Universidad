#include<iostream>
#include <vector>
using namespace std;

typedef struct {
	bool si;
	int ant;
	int pos;
}tCruce;


tCruce se_cruzan(vector<int> const& c, vector<int> const& d) {

}


bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;

	vector<int> crec, decr;
	for (int i = 0; i < n; ++i)
		cin >> crec[i];
	for (int j = 0; j < n; ++j)
		cin >> decr[j];

	tCruce tc = se_cruzan(crec, decr);
	if (tc.si)
		cout << "SI " << tc.ant << "\n";
	else
		cout << "NO " << tc.ant << " " << tc.pos << "\n";

	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}