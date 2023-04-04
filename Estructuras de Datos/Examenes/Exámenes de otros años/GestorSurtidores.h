#include <iostream>
#include <string>
#include "hashmap_eda.h"
#include "list_eda.h"
using namespace std;


class gestor {
	using surtidor = string;
	using vehiculo = string;
	using tipo_combustible = string;
	using iterator = typename list<vehiculo>::iterator;

	typedef struct {
		list<vehiculo> cola;
		unordered_map<tipo_combustible, int> combustibles;
	} info_surtidor;

	typedef struct {
		iterator it;
		surtidor s; //surtidor donde está haciendo cola
	} info_vehiculo;

	unordered_map<surtidor, info_surtidor> surtidores;
	unordered_map<vehiculo, info_vehiculo> vehiculos; //clave -> id del vehículo, valor -> puntero a su posición en la cola

public:
	//constructora vacía
	gestor() {}

	//se añade un nuevo surtidor con identicador id
	void annadir_surtidor(surtidor const& id) {
		auto itS = surtidores.find(id);
		if (itS != surtidores.end())
			throw domain_error("ESurtidorDuplicado");
		else {
			surtidores[id] = { list<vehiculo>(), unordered_map<tipo_combustible, int>() };
		}
	}

	// carga num_litros de combustible tipo_combustible en el surtidor id
	void cargar_surtidor(surtidor const& id, tipo_combustible const& cb, int num_litros) {
		auto itS = surtidores.find(id);
		if (itS == surtidores.end())
			throw domain_error("ESurtidorNoExiste");
		else
			surtidores[id].combustibles[cb] += num_litros;
	}

	//pone en espera el vehículo id_vehículo en el surtidor id
	void poner_en_espera(vehiculo const& v, surtidor const& id) {
		auto itS = surtidores.find(id);
		if (itS == surtidores.end()) //el surtidor no existe
			throw domain_error("ELlegadaVehiculo");
		else {
			auto itV = vehiculos.find(v);
			if (itV != vehiculos.end()) //el vehículo ya está esperando en otro surtidor
				throw domain_error("ELlegadaVehiculo");
			else {
				surtidores[id].cola.push_front(v);
				vehiculos[v] = { surtidores[id].cola.begin(), id };
			}
		}
	}

	//devuelve el identicador del vehículo al que se ha realizado la venta y la cantidad
	//de combustible de tipo tipo_combustible que queda aún en el surtidor.
	std::pair<vehiculo, int> vender(surtidor const& id, tipo_combustible const& cb, int num_litros) {
		auto itS = surtidores.find(id);
		if (itS == surtidores.end() || num_litros <= 0) //el surtidor no existe o num_litros es negativo
			throw domain_error("EErrorVenta");
		else {
			if (itS->valor.cola.empty()) //si no hay vehículos esperando
				throw domain_error("EErrorVenta");
			else {
				auto itC = itS->valor.combustibles.find(cb);
				if (itC == itS->valor.combustibles.end() || itC->valor < num_litros) //no hay de ese tipo combustible o no hay suficientes litros
					throw domain_error("EErrorVenta");
				else { 
					surtidores[id].combustibles[cb] -= num_litros; //se actualiza la reserva de combustible del surtidor
					vehiculo v = surtidores[id].cola.back();
					auto dlt = surtidores[id].cola.back();
					vehiculos.erase(dlt); //el vehículo abandona la gasolinera.
					surtidores[id].cola.pop_back(); //el vehículo abandona la gasolinera.

					return { v, surtidores[id].combustibles[cb] };
				}
			}
		}
	}

	//el vehículo v abandona la cola en la que está esperando y sale de la gasolinera
	void abandona(vehiculo const& v) {
		auto itV = vehiculos.find(v);
		if (itV != vehiculos.end()) {
			surtidores[vehiculos[v].s].cola.erase(itV->valor.it);
			vehiculos.erase(itV->clave);
		}
	}
};
