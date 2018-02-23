#include <iostream>
#include <string>
#include "TreeMap.h"
#include "Queue.h"
#include "Deque.h"
#include "HashMap.h"

using namespace std;

class prodCita {

	struct cita {
		int inicio;
		int final;
		string nombre;
	}; // contiene inicio, final y nombre de la persona con la qe se reune

private:

	HashMap<int, cita> citas;  //int: id cita; cita: struct definido
	int id;

public:

	prodCita() {
		id = 0;
	}

	//O(citas.size())
	Queue<int> coincidencias(int inicio, int fin) {
		Queue<int> cola;


		for (HashMap<int, cita> ::Iterator it = citas.begin(); it != citas.end(); it++) {
			if (it.value().inicio < fin && it.value().final > inicio) {
				cola.push_back(it.key());
			}
		}
		return cola;
	}

	//O(1)
	void eliminar(int id) {

		if (citas.contains(id))
			citas.erase(id);
	}

	//O(n)
	int añadir(int inicio, int fin, string nombre) {
		//if(!citas.contains(
		int i = coincidencias(inicio, fin).size();
		citas[id].inicio = inicio;
		citas[id].final = fin;
		citas[id].nombre = nombre;
		id++;
		return i;
	}

	//O(citas.size())
	void consulta(int hora) {
		Queue<int> cola = coincidencias(hora, hora);
		while (!cola.empty()) {
			cout << cola.front();
			muestraCita(citas[cola.front()]);
			//En caso de borrar despues de consulta
			//citas.erase(cola.front());
			cola.pop_front();
		}
	}

	//O(1)
	void muestraCita(cita zi) {
		cout << zi.inicio << " ";
		cout << zi.final << " ";
		cout << zi.nombre << '\n';
	}

	//O(1)
	void muestraIndi(int id) {
		if (citas.contains(id)) {
			// cout << id << " ";
			muestraCita(citas[id]);
		}
		/*
		bool borrado = false;
		HashMap<int, cita> ::Iterator it = citas.begin();
		while (it != citas.end() //&& !borrado//) {
			if (it.value().nombre == noombre) {
				cout << it.key();
				muestraCita(it.value());
			}
			it++;
		}	
		*/
	}

	//O(citas.size())
	bool libre(int comienzo, int final) {
		bool ok = true;
		for (HashMap<int, cita> ::Iterator it = citas.begin(); it != citas.end(); it++) {
			if (it.value().inicio <= final && it.value().final > comienzo) {
				ok = false;
			}
		}
		return ok;
	}

	//O(citas.size())
	void todas() {
		if (!citas.empty()) {
			for (HashMap<int, cita> ::Iterator it = citas.begin(); it != citas.end(); it++) {
				cout << it.key() << " ";
				muestraCita(it.value());
			}
		}
	}
};


int main() {
	int inicio, fin, n, id;
	string nombre, op;
	cin >> n;
	for (int i = 0; i < n; i++) {
		prodCita prod;
		cin >> op;
		while (op != "fin") {
			if (op == "cita") {
				cin >> inicio >> fin >> nombre;
				cout << prod.añadir(inicio, fin, nombre) << '\n';
			}
			else if (op == "consulta") {
				cin >> inicio;
				prod.consulta(inicio);
			}
			else if (op == "muestra") {
				cin >> id;
				prod.muestraIndi(id);
			}
			else if (op == "libre") {
				cin >> inicio >> fin;
				if (prod.libre(inicio, fin))
					cout << "true \n";
				else
					cout << "false \n";
			}
			else if (op == "borrar") {
				cin >> id;
				prod.eliminar(id);
			}
			else if (op == "todas") {
				prod.todas();
			}
			cin >> op;
		}
	}
	return 0;
}
