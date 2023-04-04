//EDURNE RUIZ. DG28


#ifndef polinomios_h
#define polinomios_h

#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class polinomio {
	struct monomio {
		int coef;
		int exp;
	};
private:
	vector<monomio> pm;
	int cont_mon;
	   
	bool exist_exp(int e, int &pos) { //true si ya hay monomio con dicho exponente, false c.c; en pos se guarda la posición que le corresponde
		int i = 0;
		while (i < cont_mon) {
			if (e < pm[i].exp) { pos = (i == 0) ? i : (e < pm[i - 1].exp) ? pos : i; }
			else if (pm[i].exp == e) {
				pos = i;
				return true;
			}
			++i;
		}
		pos = cont_mon;
		return false;

	}

	void move(int const& pos) { //deja libre la posicion "pos" del vector
		pm.push_back(pm[cont_mon-1]);
		for (int i = cont_mon - 1; pos < i; --i) {
			pm[i] = pm[i - 1];
		}
	}

	void set(int c, int e, int pos) { //
		pm[pos].coef = c;
		pm[pos].exp = e;
	}

public:

	//constructora
	polinomio() {
		cont_mon = 0;
	}

	//observadoras
	int get_coef(int pos) { return pm[pos].coef; }
	int get_exp(int pos) { return pm[pos].exp; }
	int get_cont() { return cont_mon; }
	void add_cont(int i) { cont_mon += i; }

	void add(int c, int e) {
		int pos = 0;

		if (cont_mon == 0) {
			pm.push_back({ c,e });
			++cont_mon;
		}
		else if (exist_exp(e, pos)) pm[pos].coef += c;
		else {
			if (pos == cont_mon) pm.push_back({ c,e });
			else {
				move(pos);
				set(c, e, pos);
			}
			++cont_mon;
		}
	}

	int evaluate(int const& v) {
		int p = 0;
		for (int i = 0; i < cont_mon; ++i) {
			p += (pm[i].coef)*(pow(v, pm[i].exp));
		}
		return p;
	}

};
#endif