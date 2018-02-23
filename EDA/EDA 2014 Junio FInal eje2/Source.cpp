#include <iostream>
#include <string>
#include "Arbin.h"

using namespace std;

void encuentraTesoro(const Arbin<string> &a, int dragones, int &mejor, string &puerta) {

	if (a.esVacio()) {
		return;
	}
	if (a.raiz()[0] == 'D') {
		dragones++;
	}
	else if (a.raiz()[0] == 'P') {
		if (dragones < mejor || mejor == -1) {
			mejor = dragones;
			puerta = a.raiz();
		}
	}
	encuentraTesoro(a.hijoIz(), dragones, mejor, puerta);
	encuentraTesoro(a.hijoDr(), dragones, mejor, puerta);
}

string puertaSalida(const  Arbin<string> &a) {
	int dragones = 0, mejor = -1;
	string puerta = "";
	encuentraTesoro(a, dragones, mejor, puerta);
	return puerta;
}

int main() {

	

}