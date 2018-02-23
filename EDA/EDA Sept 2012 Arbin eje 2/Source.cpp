#include <iostream>
#include <string>
#include "Arbin.h"
#include "HashMap.h"
#include "List.h"

using namespace std;

void princesa(const Arbin<string> &a, int &princesas){

	if (a.esVacio())
		return;
	if (a.raiz() == "dragon")
		return;
	else if (a.raiz() == "princesa")
		princesas++;
	princesa(a.hijoIz(), princesas);
	princesa(a.hijoDr(), princesas);
}

void princesaCercana(const Arbin<string> &a, int k, int cont, bool &exito){

	if (k == cont || a.raiz() == "dragon" || a.esVacio())
		return;
	else if (a.raiz() == "princesa"){
		exito = true;
		return;
	}
	princesaCercana(a, k + 1, cont, exito);
}

int main(){
	
	Arbin<string> a;
	int princesas = 0;
	princesa(a, princesas);

	int i = 0;
	bool exito = false;
	while ( i < a.talla() && !exito){
		int k = 0;
		princesaCercana(a, k, i, exito);
		i++;
	}
}