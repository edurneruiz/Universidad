///EDURNE RUIZ DG33
/*
Los calendarios o agendas electr´onicas controlan nuestra vida diaria. Para personas como yo, que no se nos da bien la multitarea, 
es importante tener como mucho una tarea planificada para cualquier minuto de nuestra vida. En mi calendario hay dos tipos de tareas: 
tareas ´unicas y tareas peri´odicas.
Las tareas ´unicas tienen un instante de comienzo, c y otro de finalizaci´on, f, la tarea me tendr´a ocupado durante [c, f ). 
Las tareas peri´odicas tienen adem´as de los instantes de comienzo y finalizaci´on de su primera aparici´on, un periodo de repetici´on. 
Se supone que estas tareas se repiten para siempre sin fin. Para simplificar las cosas, todos los tiempos se expresan en minutos desde un tiempo
inicial 0. 
Tu trabajo consiste en averiguar si mi calendario est´a libre de conflictos durante un periodo de mi
vida. Se considera que dos tareas est´an en conflicto si y solo si sus intervalos de tiempo se superponen,
por ejemplo [2..5) y [4..6) se superponen, pero no [2..8) con [9..10), o [2..8) con [8..10).
*/

#include <iostream>
#include "PriorityQueue.h"
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

typedef struct {
	int ini;
	int fin;
	int periodo;
} tTarea;

bool operator< (tTarea const& c1, tTarea const& c2) {
	return c1.ini < c2.ini || (c1.ini == c2.ini && c1.fin < c2.fin);
}

void inicializarAgenda(int u, int p, PriorityQueue<tTarea>  & agenda) {
	int ini = 0, fin = 0, pe = 0;
	while (u--) {
		cin >> ini >> fin;
		agenda.push({ ini,fin,pe });
	}
	while (p--) {
		cin >> ini >> fin >> pe;
		agenda.push({ ini,fin,pe });
	}
}

tTarea tarea_prioritaria(PriorityQueue<tTarea> & agenda) {
	tTarea t = agenda.top();

	if (t.periodo > 0) {
		agenda.pop();
		agenda.push({ t.ini + t.periodo, t.fin + t.periodo, t.periodo });
	}
	else
		agenda.pop();

	return t;
}


bool no_existen_conflictos(int T, PriorityQueue<tTarea> &agenda) {
	bool no = true;
	tTarea act, sig;

	act = tarea_prioritaria(agenda);
	while (no && !agenda.empty() && act.ini < T) {
		sig = tarea_prioritaria(agenda);
		no = (sig.ini < T) ? act.fin <= sig.ini : no;
		act = sig;
	}

	return no;
}

bool resuelveCaso() {
	int unic, periods, T;
	cin >> unic >> periods >> T;

	if (!std::cin)
		return false;
	else {
		PriorityQueue<tTarea> agenda;
		inicializarAgenda(unic, periods, agenda);

		if (no_existen_conflictos(T, agenda))
			cout << "NO \n";
		else
			cout << "SI \n";

		return true;
	}
}


int main() {
	while (resuelveCaso()) {}
	return 0;
}

/*
entrada:
2 0 10
2 5
4 6

0 2 100
1 4 8
5 7 8

2 1 10
8 20
1 5
6 7 10

0 2 40
16 19 10
20 25 15


salida:
SI
NO
NO
SI
*/