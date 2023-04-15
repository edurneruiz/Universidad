///EDURNE RUIZ DG33
/*
En el Hospital ACR (Aqu´ı Curamos R´apido) se han puesto a mejorar las Urgencias para que los enfermos que llegan con 
dolencias m´as graves sean atendidos antes que los dem´as. Para eso, han comprado una UCM (Unidad de Catalogaci´on M´edica) que
es capaz de valorar instant´aneamente el estado de un paciente con un n´umero entero entre 0 y 1.000.000, donde 0 indica 
que su dolencia es menor (quiz´a incluso inexistente y sea un mero hipocondr´ıaco) y 1.000.000 indica que el enfermo 
est´a casi caminando hacia la luz.
Por desgracia, la afluencia de enfermos es tal que incluso as´ı es muy complicado saber r´apidamente qui´en deber´ıa ser 
el pr´oximo en ser atendido. No hacen m´as que entrar pacientes nuevos a la vez que los m´as graves son atendidos, y no 
es f´acil mantenerlos ordenados. Cuando un m´edico queda libre, debe ser atendido el enfermo a la espera con una
valoraci´on m´as grave. Si hay dos pacientes evaluados con la misma gravedad, deber´a ser atendido el que
m´as tiempo lleve esperando.
*/

#include <iostream>
#include "PriorityQueue.h"
#include <fstream>
#include <string>
using namespace std;

typedef struct {
	string nombre; //nombre paciente
	long long int gravedad; //gravedad de la lesion
	int espera; //tiempo esperando
} tPaciente;

bool operator< (tPaciente const& p1, tPaciente const& p2) {
	return p2.gravedad < p1.gravedad || (p2.gravedad == p1.gravedad && p1.espera < p2.espera);
}

void sucesion_eventos(int e, PriorityQueue<tPaciente> & pacientes) {
	char evento; string nombre; long long int g;
	int espera = 1;

	while (e--) {
		cin >> evento;
		switch (evento) {
		case 'I':
			cin >> nombre >> g;
			pacientes.push({ nombre, g, espera++ });
			break;
		case 'A':
			cout << pacientes.top().nombre << '\n';
			pacientes.pop();
			break;
		}
	}
}

bool resuelveCaso() {
	int eventos;
	cin >> eventos;

	if (eventos == 0)
		return false;
	else {
		PriorityQueue<tPaciente> pacientes;
		sucesion_eventos(eventos, pacientes);
		cout << "--- \n";
		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
9
I Alberto 4000
I Pepe 3000
A
I Rosa 2000
I Laura 5000
A
I Sara 3000
A
A
0
salida:
Alberto
Laura
Pepe
Sara
---

*/