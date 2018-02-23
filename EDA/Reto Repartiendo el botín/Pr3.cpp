#include <iostream>
#include <string>
#include "Queue.h"
#include "Deque.h"

using namespace std;



void muestraCola(Deque<int> cola1, int aux, int aux2, int ladrones, int nbilletes) {

	int nladrones = ladrones;
	int j = 1;

	while (ladrones != 0) {
		int suma = 0, i = 1;
		int resto = j % nladrones;

		while (i <= nbilletes) {

			aux = cola1.front();
			if((i % nladrones) == resto) suma += aux;
			cola1.pop_front();
			cola1.push_back(aux);
			i++;
		}

		cout << suma << ":";

		i = 1;

		while (i <= nbilletes) {

			aux = cola1.front();
			if ((i % nladrones) == resto) cout << " " << aux ;
			cola1.pop_front();
			cola1.push_back(aux);
			i++;
		}

		cout << "\n";
		ladrones--;
		j++;
	}


}

void muestraPila(Deque<int> cola1, int aux, int aux2, int ladrones, int nbilletes) { 


	int nladrones = ladrones;
	int j = 1;

	while (ladrones != 0) {
		int suma = 0, i = 1;
		int resto = j % nladrones;

		while (i <= nbilletes) {

			aux = cola1.front();
			if ((i % nladrones) == resto) suma += aux;
			cola1.pop_front();
			cola1.push_back(aux);
			i++;
		}

		cout << suma << ":";

		i = nbilletes;

		while (i > 0) {

			aux = cola1.back();
			if ((i % nladrones) == resto) cout << " " << aux;
			cola1.pop_back();
			cola1.push_front(aux);
			i--;
		}

		cout << "\n";
		ladrones--;
		j++;
	}
}


int main() {

	int nbilletes, ladrones, billete, aux = 0;
	string tipo;


	while (cin >> nbilletes >> ladrones >> tipo) {

		Deque<int> cola1;
		int aux2 = ladrones;

		for (int i = 0; i < nbilletes; i++) {

			cin >> billete;
			cola1.push_back(billete);
		}

		if (tipo == "cola") {

			muestraCola(cola1, aux, aux2, ladrones, nbilletes);
		}
		else if (tipo == "pila") {
			muestraPila(cola1, aux, aux2, ladrones, nbilletes);
		}

		cout << "---" << endl;

	}
	return 0;
}