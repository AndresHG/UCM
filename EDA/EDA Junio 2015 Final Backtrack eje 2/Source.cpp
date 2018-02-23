#include <iostream>
#include <string>

using namespace std;


const int n = 5;
typedef pair<int, int> pares[n];

void actividadesSolapadas(const pares &par, int fin, int k, int r, int cont, bool marcas[n], pares &sol, int mayor){

	
	for (int i = 0; i < n; i++){
	
		if (!marcas[i] && !interseccion(mayor, par[i].first)){
			int h = mayor;
			mayor = par[i].second;
			marcas[i] = true;
			cont++;

			if (cont >= r)
				tratarSolucion(sol);
			actividadesSolapadas(par, fin, k+1, r, cont, marcas, sol, mayor);
			mayor = h;
			marcas[i] = false;
			cont--;
		}
	}
}

bool interseccion(int x, int y){
	return x <= y ? false : true;
}

void tratarSolucion(pares &sol){


	return;
}

int main(){

	pares par;
	return par[2].first == 2 ? true : false;
}