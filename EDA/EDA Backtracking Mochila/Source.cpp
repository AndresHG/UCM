#include <iostream> 
#include <string>

using namespace std;

const int n = 8;

//No esta bien que se diga, aunqeu hay ideas correctes


int llamadaInicial(int valor[], int peso[], int m) {

	int max=0, k, suma=0, maxValor = -1;
	bool marca[n] = { false };
	mochila(valor, peso, m, max, k, suma, marca, maxValor);
	return maxValor;
}

//Inicializamos marcas a false;
void mochila(int valor[], int peso[], int m, int max, int k, int sumaPeso, bool marca[], int &maxValor) {

	int i = k; //int i=0;
	while (i < n && !marca[i] && sumaPeso + peso[i] < m) {
		sumaPeso += peso[i];
		max += valor[i];
		marca[i] = true;
		if (max > maxValor || maxValor == -1)
			maxValor = max;
		mochila(valor, peso, m, max, k + 1, sumaPeso, marca, maxValor);
		sumaPeso -= peso[i];
		max -= valor[i];
		marca[i] = false;
	}
}


int main() {

	system("pause");
	return 0;
}