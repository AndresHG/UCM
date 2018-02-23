#include <iostream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <conio.h>


using namespace std;


const int n = 8;

struct tCasilla{
	int fila;
	int columna;
};

bool mueve(char dir, int &x, int &y) {


	switch (dir) {
	case 'N':
		if (x > 0)
			x--;
		break;
	case 'S':
		if (x < n-1)
			x++;
		break;
	case 'E':
		if (y < n - 1)
			y++;
		break;
	case 'O':
		if (y > 0)
			y--;
		break;
	}

	return true;
}

//Iniciamos marcas a false
void salirLab(bool matriz[][n], int x, int y, bool &exito, bool marcas[][n], int k, tCasilla sol[]) {

	int i = 0;

	while(i < 4 && !exito) {
		mueve("SEON"[i], x, y);
		if (matriz[x][y] && !marcas[x][y]) {
			marcas[x][y] = true;
			sol[k].fila = x;
			sol[k].columna = y;
			if (x == n - 1 && y == n - 1) {
				//Imprime pantalla
				exito = true;
				return;
			}
			else
				salirLab(matriz, x, y, exito, marcas, k+1, sol);
			marcas[x][y] = false;
		}
		mueve("NOES"[i], x, y);
		i++;
	}
}

int main() {
	//Matriz es el laberinto, marcas es la matriz de marcas y habria que iniciarla a false
	bool matriz[n][n], marcas[n][n];
	bool exito = false;
	tCasilla sol[n*n];
	int x = 0, y = 0, k =0;
	salirLab(matriz, x, y, exito, marcas, k, sol);

	system("pause");
	return 0;
}