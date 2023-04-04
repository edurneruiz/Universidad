#include <iostream>
using namespace std;

class fecha {
	int dia;
	int mes;
	int a�o;

public:

	fecha(int d = 0, int h = 0, int m = 0) {
		dia = d; mes = h; a�o = m;
	}

	int getDia() { return dia; }
	int getMes() { return mes; }
	int getA�o() { return a�o; }

	bool operator<(fecha f) const {
		int dd = f.getDia(), mm = f.getMes(), aa = f.getA�o();
		if (a�o < aa) return true;
		else if (a�o > aa) return false;
		else 
			return (mes == mm) ? (dia < dd) : (mes < mm);
	}

	void read(std::istream & input = std::cin) {
		char c; int h, m, d;
		input >> d >> c >> h >> c >> m;
		dia = d; mes = h; a�o = m;
	}

	void print(std::ostream& o = std::cout) const {
		o << to_string(dia) + "/" + to_string(mes) + "/" + to_string(a�o);
	}
};

inline std::ostream & operator<<(std::ostream & salida, fecha const& f) {
	f.print(salida);
	return salida;
}

inline std::istream & operator>>(std::istream & entrada, fecha & f) {
	f.read(entrada);
	return entrada;
}
