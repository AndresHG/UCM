#include <iostream>
#include "HashMap.h"
#include "TreeMap.h"
#include "List.h"

using namespace std;

class {

	HashMap<string, TreeMap<string, int> > asignaturas;  //siendo asignaturas el hashmap que contiene a el treemap de alumnos con sus correspondientes faltas

private:
	

public:

	HashMap<string, int> noFaltas() {
		HashMap<string, int> lista;
		HashMap<string, TreeMap<string, int> >::Iterator itAsignaturas = asignaturas.begin();
		for (itAsignaturas; itAsignaturas != asignaturas.end(); itAsignaturas++) {
			TreeMap<string, int>::Iterator itAlumnos = itAsignaturas.value().begin();
			for (itAlumnos; itAlumnos != itAsignaturas.value().end(); itAlumnos++) {
				if (itAlumnos.value() != 0 && lista.contains(itAlumnos.key())) {
					lista.erase(itAlumnos.key());
				}
				if (itAlumnos.value() == 0 && !lista.contains(itAlumnos.key())) {
					lista[itAlumnos.key()];
				}
			}
		}
	}

	int totalFlatas(string id) {
		int total;
		HashMap<string, TreeMap<string, int> >::Iterator itAsignaturas = asignaturas.begin();
		for (itAsignaturas; itAsignaturas != asignaturas.end(); itAsignaturas++) {
			if (itAsignaturas.value().contains(id))
				total += itAsignaturas.value()[id];
				//asignaturas[itAsignaturas.key()][id];
		}
		return total;
	}

};


int main() {



}