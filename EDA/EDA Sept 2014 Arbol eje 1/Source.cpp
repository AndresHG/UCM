#include <iostream>
#include <string>
#include "Arbin.h"
#include "HashMap.h"
#include "List.h"

using namespace std;

bool gene(const Arbin<int> &a, int años, bool iz, int hermano){

	if (a.esVacio())
		return true;
	if (iz) {
		if (a.raiz() + 18 > años)
			return false;
	}
	else {
		if (a.raiz() + 18 > años && a.raiz() + 2 > hermano)
			return false;
	}
	//Al ser obligatorio que el primer hijo sea el izquierdo, el programa no explota ya que hijoIz().raiz() va a tener un valor, y si el hijoIz() era vacio,
	//el hijoDr también lo es y devolvera true directamente, ya que entraria en el primer if
	return gene(a.hijoIz(), a.raiz(), true, 0) && gene(a.hijoDr(), a.raiz(), false, a.hijoIz().raiz());
}

bool esGenealogico(const Arbin<int> &a) {

	//Llamada inicial
	return gene(a.hijoIz(), a.raiz(), true, 0) && gene(a.hijoDr(), a.raiz(), false, a.hijoIz().raiz());
}

int main(){
	
	
}