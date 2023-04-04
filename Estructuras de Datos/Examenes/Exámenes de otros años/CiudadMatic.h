#include <iostream>
#include <string>
#include "hashmap_eda.h"
#include "list_eda.h"
using namespace std;

class ciudad {
	using tipo_edificio = string;
	using edificio = string;

	typedef struct {
		int cc; //coste de construcción
		int ixt; //cantidad de impuestos generada por turno
		int cb; //calidad base -> max de turnos sin reparar
	} info_tipo;

	typedef struct {
		tipo_edificio t; //qué tipo de edificio es
		info_tipo info;
	} info_edificio;

	int presupuesto; //dinero disponible para ser gastado
	unordered_map<edificio, info_edificio> eciudad;
	unordered_map<tipo_edificio, list<edificio>> ext; //edificios por tipo
	unordered_map<tipo_edificio, info_tipo> tipos;

public:

	//inicializa una nueva ciudad vacía, con el dinero que se pase como argumento disponible para ser gastado.
	ciudad(int d) {
		presupuesto = d;
	}

	//añade un nuevo tipo de edificio al sistema
	void nuevoTipo(tipo_edificio const& ti, int const& cc, int const& imp, int const& cb) {
		tipos[ti] = { cc, imp, cb };
	}

	//añade el edificio ED del tipo TI a la ciudad
	void insertaEdificio(tipo_edificio const& ti, edificio const& ed) {
		if (tipos[ti].cc > presupuesto) {
			eciudad.insert(ed);
			ext[ti].push_back(ed);
			presupuesto -= tipos[ti].cc;
		}
	}

	//repara el edificio con un coste del 10 % del coste de construcción
	void reparaEdificio(edificio const& ed) {
		auto itE = eciudad.find(ed);
		if (itE != eciudad.end()) {
			presupuesto -= itE->valor.info.cc*0.1;
		}
	}

	int finTurno() {
		auto itE = eciudad.begin();

		while (itE != eciudad.end()) {
			presupuesto += itE->valor.info.ixt;
			--itE->valor.info.cb;
			if (itE->valor.info.cb == 0) {
				ext[itE->valor.t].erase(itE.operator*);
				eciudad.erase(itE->clave);
			}
			++itE;
		}
		
		return presupuesto;
	}

	vector<edificio> listaEdificios(tipo_edificio const& ti) {
		vector<edificio> v;
		for (edificio e : ext[ti]) {
			v.push_back(e);
		}
		return v;
	}
};

