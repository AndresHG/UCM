#include <iostream>
#include <string>
#include "HashMap.h"
#include "TreeMap.h"
#include "List.h"

using namespace std;

class noClienteException: public exception{};

class agencia {
private:
	typedef string cliente, hotel;
	class Nada{};

	HashMap<cliente, hotel> clientes;
	TreeMap<hotel, HashMap<cliente, Nada> > hoteles;

public:
	void aloja(cliente c, hotel h) {
		clientes[c] = h;
		hoteles[h][c];
	}
	void desaloja(cliente c) {
		if (clientes.contains(c)) {
			hoteles[clientes[c]].erase(c);
			clientes.erase(c);
		}
	}
	cliente alojamiento(cliente c) {
		if (clientes.contains(c)) {
			return clientes[c];
		}
		else
			throw new noClienteException();
	}
	List<hotel> listado_hoteles() {
		List<hotel> lista;
		TreeMap<hotel, HashMap<cliente, Nada> >::ConstIterator it = hoteles.cbegin();
		for (it; it != hoteles.cend(); it++) {
			lista.push_back(it.key());
		}
		return lista;
	}
	List<cliente> huespedes(hotel h) {
		List<cliente> lista;
		HashMap<cliente, hotel>::ConstIterator it = clientes.cbegin();
		for (it; it != clientes.cend(); it++) {
			lista.push_back(it.key());
		}
		return lista;
	}
};


int main() {

}