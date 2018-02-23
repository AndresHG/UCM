#include <iostream>
#include <string>
#include "HashMap.h"
#include "TreeMap.h"
#include "List.h"

using namespace std;


class EspacioMatic {

private:
	//  id ,          Nombre modulo, nivel 
	HashMap<int, TreeMap <string, int>> naves;

public:

	EspacioMatic() {
	}

	void nuevaNave(int num) {
		if (!naves.contains(num)) {
			naves[num];
		}
	}

	void equipaNave(int num, string Nombre, int nivel) {
		// suponemos que siempre existe la nave
		naves[num][Nombre] += nivel;
	}


	bool estropeaNave(int num, string Nombre) {

		if (naves[num].contains(Nombre) && naves[num][Nombre] > 0) { naves[num][Nombre]--; return true;}
		return false;
	}

	List<int> navesDefectuosas() {

		HashMap<int, TreeMap <string, int>> ::Iterator it_naves = naves.begin();
		List<int> defectuosos;

		for (it_naves; it_naves != naves.end(); it_naves++) {

			TreeMap <string, int > ::Iterator it_nombres = it_naves.value().begin();

			while (it_nombres != it_naves.value().end() && it_nombres.value() != 0) {
				it_nombres++;
			}

			if (it_nombres != it_naves.value().end()) {
				defectuosos.push_back(it_naves.key());
			}
		}
		return defectuosos;
	}


	List<string> modulosNave(int num) {

		TreeMap <string, int > ::Iterator it_nombres = naves[num].begin();
		List<string> modulos;

		for (it_nombres; it_nombres != naves[num].end(); it_nombres++) {

			modulos.push_back(it_nombres.key());
		}
		return modulos;
	}
};


int main() {


}