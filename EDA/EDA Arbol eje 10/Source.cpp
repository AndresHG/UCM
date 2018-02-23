#include <iostream>
#include <string>
#include "Arbin.h"

using namespace std;


bool sumarr(Arbin<int> const &a, int suma, int total){

	if (a.esVacio())
		return suma == total;
	else
		return sumarr(a.hijoIz(), suma + a.raiz(), total) || sumarr(a.hijoDr(), suma + a.raiz(), total);
}

int main(){
	int total = 7; int suma = 0;
	Arbin<int> a;
	a = Arbin<int>(Arbin<int>(Arbin<int>(7, 11, 2), 4, NULL), 5, Arbin<int>(13, 8, Arbin<int>(NULL, 4, 1)));
	 sumarr(a, suma, total)? cout << "Contiene\n" : cout << "No contiene\n";

	 system("pause");
}