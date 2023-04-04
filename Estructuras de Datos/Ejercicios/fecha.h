#include <iostream>
using namespace std;

class fecha {
	int dia;
	int hora;
	int minuto;

public:

	fecha(int d = 0, int h = 0, int m = 0) {
		dia = d; hora = h; minuto = m;
	}

	int getDia() { return dia; }
	int getHora() { return hora; }
	int getMinuto() { return minuto; }

	bool operator<(fecha f) const {
		if (dia < f.getDia()) return true;
		else if (dia > f.getDia()) return false;
		else 
			return hora * 60 + minuto < f.getHora() * 60 + f.getMinuto();
	}

	void read(std::istream & input = std::cin) {
		char c; int h, m, d;
		input >> d >> h >> c >> m;
		dia = d; hora = h; minuto = m;
	}

	void print(std::ostream& o = std::cout) const {
		if (hora < 10) o << "0" + to_string(hora);
		else o << hora;
		if (minuto < 10) o << ':' << "0" + to_string(minuto);
		else o << ':' << minuto;
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
