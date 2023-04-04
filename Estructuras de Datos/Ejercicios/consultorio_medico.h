#include <iostream>
#include <string>
#include <vector>
#include "fecha.h"
#include "set_eda.h"
#include "hashmap_eda.h"
#include "treemap_eda.h"
using namespace std;

using medico = string;
using paciente = string;


class consultorio {
	using info_paciente = pair<paciente, fecha>;
	using consulta = map<fecha, paciente>; //clave -> hora de la consulta, valor -> paciente en esa hora ///ordenados

	unordered_map<medico, consulta> meds; //clave -> medico, valor -> conjunto de pacientes de ese médico

public :

	void nuevoMedico(medico const& m) {
		auto itM = meds.find(m);
		if (itM == meds.end())
			meds.insert(m);
	}

	void pideConsulta(paciente const& p, medico const& m, fecha const& f) {
		auto itM = meds.find(m);
		if (itM == meds.end()) //si el médico no existe
			throw domain_error("Medico no existente");
		else {
			auto & cm = itM->valor;
			auto itF = cm.find(f);
			if (itF != cm.end()) //si la fecha para ese médico está ocupada
				throw domain_error("Fecha ocupada");
			else {
				cm[f] = p; //insertamos la fecha y le asignamos su paciente
			}
		}
	}

	paciente siguientePaciente(medico const& m) {
		auto itM = meds.find(m);
		if (itM == meds.end()) //si el médico no existe
			throw domain_error("Medico no existente");
		else {
			auto & cm = itM->valor;
			if (cm.empty())
				throw domain_error("No hay pacientes");
			else {
				auto sig = cm.begin();
				return sig->valor;
			}
		}
	}

	void atiendeConsulta(medico const& m) {
		auto itM = meds.find(m);
		if (itM == meds.end()) //si el médico no existe
			throw domain_error("Medico no existente");
		else {
			auto & cm = itM->valor;
			if (cm.empty())
				throw domain_error("No hay pacientes");
			else {
				auto sig = cm.begin();
				cm.erase(sig->clave);
			}
		}
	}

	vector<info_paciente> listaPacientes(medico const& m, int dia) {
		fecha f1(dia), f2(dia + 1);
		auto itM = meds.find(m);
		if (itM == meds.end()) //si el médico no existe
			throw domain_error("Medico no existente");
		else {
			vector<info_paciente> l;
			auto itF = itM->valor.begin();
			while (itF != itM->valor.end() && itF->clave < f2) {
				if (f1 < itF->clave)
					l.push_back({ itF->valor, itF->clave });
				++itF;
			}

			return l;
		}
	}
	

};