#include <iostream>
#include <string>

using namespace std;

const int n = 8;
const int m = 4;

void irDeCompras(int sol[n], int marcas[m], int k, int coste, int mejor, int best[n], int precios[n][m]){

	if (k == n){
		if (coste < mejor || mejor == -1){
			for (int i = 0; i < n; i++)
				best[i] = sol[i];
		}
	}
	else{
		for (int i = 0; i < m; i++){
			if (marcas[i] <= 3){
				marcas[i]++;
				coste += precios[k][m];
				sol[k] = i;
				irDeCompras(sol, marcas, k+1, coste, mejor, best, precios);
				marcas[i]--;
				coste -= precios[k][m];
			}
		}
	}
}


int main(){



	system("pause");
	return 0;
}