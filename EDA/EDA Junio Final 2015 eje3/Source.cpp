#include <iostream>
#include <string>
#include "Arbin.h"

using namespace std;

void calculaTiempo(const Arbin<char> &a, int horasActuales, int &total) {

	if (a.esVacio()) {
		return;
	}
	horasActuales++;
	if (a.raiz() == 'x') {
		total += 2*horasActuales;
	}
	calculaTiempo(a.hijoIz(), horasActuales, total);
	calculaTiempo(a.hijoDr(), horasActuales, total);
}

void tiempoAyuda(const Arbin<char> &a) {

	int horas = 0, total = 0;
	calculaTiempo(a, horas, total);
}

int main() {


}