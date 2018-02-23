/* Andrés Herranz González 
Guillermo Rius García 
Facultad de Informatica 1º D
Universidad Complutense de Madrid

 Debido a mi versión de visual  Studio, me he visto obligado a usar la libreria stdafx.cpp, la cual seguramente usted no tenga que usar
 de modo que con solo borrarla, el programa deberia compilar correctamente.
*/

#include "stdafx.h"
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

int const MAX = 6;
typedef int tMatriz[MAX][MAX];
typedef enum {Esc, Arriba, Abajo, Derecha, Izquierda, Enter} tAccion;

void crearTabla(tMatriz v, int casillas, int puntos, int totalpuntos);
void rellenarMatriz(tMatriz v, int casillas);
void colorFondo(int color);
void mueveFichas(tMatriz v, tAccion accion, int casillas, int &movimientos);
int log2(int valor);
void carga(tMatriz v, int &puntos, int &dimensiones);
void posAleatoria(tMatriz v, int casillas);
void guarda(tMatriz v, int puntos, int casillas);
tAccion leeAccion();
void combinaFichas(tMatriz v, tAccion accion, int &puntos, int casillas);
bool lleno(const tMatriz v, int casillas);
int fMenu(int opcion);
int fMenu2(int opcion);
int Tmayor(const tMatriz v);
void fInstrucciones(string nombre);

int main(){

	tMatriz v;
	tAccion accion = Derecha;
	string nombre;
	int casillas, opcion=0, puntos=0, totalpuntos=0, dimensiones, movimientos=0, modo, mayor=1;
	srand(time(NULL));

	for (int q=0; q<11; q++)
		cout << endl;
	cout << setw(43) << "Bienvenido" << endl;
	Sleep(2000);
	opcion = fMenu(opcion);

	while (opcion != 4){
		puntos=0;
		totalpuntos=0;
		if(opcion==1){
			system("cls");
			cout << "Indique el tamaño del cuadro: ";
			cin >> casillas;
			while (casillas > MAX)
				cin >> casillas;
			for (int a= 0; a < casillas; a++){
				for (int b=0; b < casillas; b++)
					v[a][b]=1;
			}
			for (int i=0; i<2; i++)
				posAleatoria(v, casillas);
			accion = Derecha;
		}
		else if (opcion==2){
			system("cls");
			carga(v, totalpuntos, dimensiones);
			casillas= dimensiones;
			accion = Derecha;
		}
		else if (opcion == 3){
			system("cls");
			nombre = "hola.txt";
			fInstrucciones(nombre);
			accion = Esc;
			system("pause");
		}
		while (accion != Esc){
			crearTabla(v, casillas, puntos, totalpuntos);
			modo =0;
			movimientos=0;
			puntos=0;
			accion = leeAccion();
			system("cls");
			mueveFichas(v, accion, casillas, movimientos);
			combinaFichas(v, accion, puntos, casillas);
			mueveFichas(v, accion, casillas, movimientos);
			totalpuntos += puntos;
			if (!lleno(v, casillas)){
				if (puntos ==0 && movimientos ==0)
					cout << "Movimiento erroneo" << endl;
				else
					posAleatoria(v, casillas);
			}
			else {
				mueveFichas(v, accion, casillas, movimientos);
				combinaFichas(v, accion, puntos, casillas);
				mueveFichas(v, accion, casillas, movimientos);
				totalpuntos += puntos;
				if (puntos ==0 && movimientos ==0){
					for (int q=0; q<11; q++)
						cout << endl;
					cout << setw(43) << "Has perdido" << endl;
					Sleep(2000);
					accion = Esc;
					modo =1;
				}
			}
			mayor = Tmayor(v);
			if (mayor == 2048){
				for (int q=0; q<11; q++)
					cout << endl;
				cout << setw(43) << "Has Ganado" << endl;
				Sleep(2000);
				accion = Esc;
				modo =1;
			}
			if (accion == Esc && modo == 0){
				opcion = fMenu2(opcion);
				if (opcion == 1){
					guarda(v, totalpuntos, casillas);
					accion = Derecha;
				}
				else if (opcion == 2)
					guarda(v, totalpuntos, casillas);
				else if (opcion == 3){
					system("cls");
					carga(v, puntos, dimensiones);
					puntos = 0;
					accion = Derecha;
				}
			}
			system("cls");	
		}
	opcion = fMenu(opcion);
	}
}

void crearTabla(tMatriz v, int casillas, int puntos, int totalpuntos){

	cout << "Puntos:" << setw(4) << puntos;
	cout << setw(casillas*3) << "Total:" << setw(5) << totalpuntos << endl;
	int i=0, n=0, l=0;
	cout << char(218);
	for (int i=0; i < casillas; i++){
		cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
		if (i < (casillas -1))
			cout << char(194);
	}
	cout << char(191);
	cout << endl;
	for (int m=0; m < casillas; m++){
		cout << char(179);
		l=0;
		for (int i=0; i < casillas; i++){
			colorFondo(log2(v[n][l]));
			cout <<  "      ";
			colorFondo(0);
			cout << char(179);
			l++;
		}
			cout << endl;
			l=0;
		for (int i=0; i < casillas; i++){
			cout << char(179);
			colorFondo(log2(v[n][l]));
			if(v[n][l] != 1)
				cout << setw(5) << v[n][l];	
			else
				cout << "     ";
			if (i < casillas)
				cout << " ";
			l++;
			colorFondo(0);
		}
		cout << char(179);
		cout << endl;
		cout << char(179);
		l=0;
		for (int i=0; i < casillas; i++){
			colorFondo(log2(v[n][l]));
			cout <<  "      ";
			colorFondo(0);
			cout << char(179);
			l++;
		}
		cout << endl;
		if (m < casillas - 1)
			cout << char(195);
		else
			cout << char(192);
		for (int i=0; i < casillas; i++){
			cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
			if (m < casillas-1){
				if (i < (casillas -1))
					cout << char(197);
			}
			else{
				if (i < (casillas -1))
					cout << char(193);
			}
		}
		if (m < casillas -1)
			cout << char(180);
		else
			cout << char(217);
		cout << endl;
		n++;
	}
}

void colorFondo(int color) {
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void mueveFichas(tMatriz v, tAccion accion, int casillas, int &movimientos){
	
	int pos = casillas -1, cont;

	switch (accion){
	case Arriba:
		for (int b = 0; b <= pos; b++){
			cont = -1;
			for (int a = 0; a <= pos; a++){
				if (v[a][b] == 1 && cont == -1)
					cont = a;
				else if (v[a][b] != 1 && cont != -1){
					v[cont][b] = v[a][b];
					v[a][b]=1;
					cont++;
					movimientos++;
				}
			}
		}
		break;
	case Abajo:
		for (int b = pos; b >= 0; b--){
			cont = -1;
			for (int a = pos; a >= 0; a--){
				if (v[a][b] == 1 && cont == -1)
					cont = a;
				else if (v[a][b] != 1 && cont != -1){
					v[cont][b] = v[a][b];
					v[a][b]=1;
					cont--;
					movimientos++;
				}
			}
		}
		break;
	case Derecha:
		for (int a = pos; a >= 0; a--){
			cont = -1;
			for (int b = pos; b >= 0; b--){
				if (v[a][b] == 1 && cont == -1)
					cont = b;
				else if (v[a][b] != 1 && cont != -1){
					v[a][cont] = v[a][b];
					v[a][b]=1;
					cont--;
					movimientos++;
				}
			}
		}
		break;
	case Izquierda:
		for (int a = 0; a <= pos; a++){
			cont = -1;
			for (int b = 0; b <= pos; b++){
				if (v[a][b] == 1 && cont == -1)
					cont = b;
				else if (v[a][b] != 1 && cont != -1){
					v[a][cont] = v[a][b];
					v[a][b]=1;
					cont++;
					movimientos++;
				}
			}
		}
		break;
	}
}

void carga(tMatriz v, int &puntos, int &dimensiones){

	ifstream archivo;
	string nombre;
	int x;

	cout << "Introduzca el nombre del archivo de la partida guardada:" << endl;
	cin  >> nombre;
	archivo.open(nombre);
	if(archivo.is_open()){
		archivo >> dimensiones;
		for (int a=0; a < dimensiones; a++){
			for (int b=0; b < dimensiones; b++){
				archivo >> x;
				v[a][b]=x;
			}
		}
		archivo >> puntos;
	}
	archivo.close();
}

int log2(int valor){

	int resultado;

	resultado= log(valor) / log(2);
	return resultado;
}

void posAleatoria(tMatriz v, int casillas){  

	int n, l, w, z;

	n = rand()%(casillas-1);
	l = rand()%(casillas-1);
	while (v[n][l]!=1){
		n = rand()%casillas;
		l = rand()%casillas;
	}
	z = rand()%99;
	if (z<95)
		w = 2;
	else 
		w=4;
	v[n][l]= w;
}

void guarda(tMatriz v, int puntos, int casillas){

	ofstream archivo;
	string nombre;
	int x;

	system("cls");
	cout << "Introduzca el nombre para guardar:" << endl;
	cin  >> nombre;
	archivo.open(nombre);
	if(archivo.is_open()){
		archivo << casillas << endl;
		for (int a=0; a < casillas; a++){
			for (int b=0; b < casillas; b++){
				x = v[a][b];
				archivo << x << endl;
			}
		}
		archivo << puntos;
		archivo.close();
	}
	else
		cout << "Error al abrir el archivo" << endl;
}   // Probar

tAccion leeAccion(){

	int dir;
	tAccion accion;
	cin.sync();
	dir = _getch();
	
	if(dir == 0xe0) {
		dir = _getch();
		switch(dir){
		case 72: 
			accion = Arriba; break;
		case 80:
			accion = Abajo; break;
		case 77:
			accion = Derecha; break;
		case 75:
			accion = Izquierda; break;
		case 13:
			accion = Enter; break;
		}
	}
	else
		accion = Esc;
	return accion;
}

void combinaFichas(tMatriz v, tAccion accion, int &puntos, int casillas){

	switch (accion){
	case Arriba:
		for (int b = 0; b <= casillas -1; b++){
			for (int a = 1; a <= casillas -1; a++){
				if (v[a][b] == v[a-1][b] && v[a][b] != 1){
					v[a-1][b] = 2* v[a][b];
					puntos += 2*v[a][b];
					v[a][b] = 1;
				}
			}
		}
		break;
	case Abajo:
		for (int b = casillas -1; b >= 0; b--){
			for (int a = casillas -2; a >= 0; a--){
				if (v[a][b] == v[a+1][b] && v[a][b] != 1){
					v[a+1][b] = 2* v[a][b];
					puntos += 2*v[a][b];
					v[a][b] = 1;
				}
			}
		}
		break;
	case Derecha:
		for (int a = casillas -1; a >= 0; a--){
			for (int b = casillas -2; b >= 0; b--){
				if (v[a][b] == v[a][b+1] && v[a][b] != 1){
					v[a][b+1] = 2* v[a][b];
					puntos += 2*v[a][b];
					v[a][b] = 1;
				}
			}
		}
		break;
	case Izquierda:
		for (int a = 0; a <= casillas -1; a++){
			for (int b = 1; b <= casillas -1; b++){
				if (v[a][b] == v[a][b-1] && v[a][b] != 1){
					v[a][b-1] = 2* v[a][b];
					puntos += 2*v[a][b];
					v[a][b] = 1;
				}
			}
		}
		break;
	}
}

bool lleno(const tMatriz v, int casillas){

	int a=0, b=0;
	bool lleno = true;

	while (a < casillas && lleno){
		while (b < casillas && lleno){
			if (v[a][b] != 1)
				b++;
			else
				lleno = false;
		}
		b=0;
		a++;
	}
	return lleno;
}

int Tmayor(const tMatriz v){

	int mayor = 1;
	mayor = 1;
	for(int a = 0; a < MAX; a++)
		for (int b = 0; b < MAX; b++)
			if (mayor < v[a][b])
				mayor = v[a][b];
	return mayor;
}

int fMenu(int opcion){

	tAccion accion;

	opcion=1;
	system("cls");
	for (int q=0; q<6; q++)
		cout << endl;
	cout << setw(35) << "-->" << setw(6) << "Nueva Partida" << endl;
	cout << setw(42) << "Cargar Partidas" << endl;
	cout << setw(41) << "Instrucciones" << endl;
	cout << setw(37) << "Salir" << endl;
	accion = leeAccion();
	while (accion == Arriba || accion == Abajo){
		system("cls");
		for (int q=0; q<6; q++)
			cout << endl;
		if (accion == Arriba && opcion > 1)
			opcion--;
		else if (accion == Abajo && opcion < 4)
			opcion++;
		if (opcion == 1)
			cout << setw(35) << "-->" << setw(6) << "Nueva Partida" << endl;
		else
			cout << setw(41) << "Nueva Partida" << endl;
		if (opcion == 2)
			cout << setw(35) << "-->" << setw(7) << "Cargar Partida" << endl;
		else
			cout << setw(42) << "Cargar Partidas" << endl;
		if (opcion == 3)
			cout << setw(35) << "-->" << setw(7) << "Instrucciones" << endl;
		else
			cout << setw(41) << "Instrucciones" << endl;
		if (opcion == 4)
			cout << setw(35) << "-->" << setw(7) << "Salir" << endl;
		else
			cout << setw(37) << "Salir" << endl;
		accion = leeAccion();
	}

	return opcion;
}

int fMenu2(int opcion){

	tAccion accion;

	opcion=1;
	system("cls");
	for (int q=0; q<6; q++)
		cout << endl;
	cout << setw(35) << "-->" << setw(6) << "Guardar y continuar" << endl;
	cout << setw(41) << "Guardar y salir" << endl;
	cout << setw(41) << "Cargar Partidas" << endl;
	cout << setw(42) << "Salir sin guardar" << endl;
	accion = leeAccion();
	while (accion == Arriba || accion == Abajo){
		system("cls");
		for (int q=0; q<6; q++)
			cout << endl;
		if (accion == Arriba && opcion > 1)
			opcion--;
		else if (accion == Abajo && opcion < 4)
			opcion++;
		if (opcion == 1)
			cout << setw(35) << "-->" << setw(6) << "Guardar y continuar" << endl;
		else
			cout << setw(43) << "Guardar y continuar" << endl;
		if (opcion == 2)
			cout << setw(35) << "-->" << setw(7) << "Guardar y salir" << endl;
		else
			cout << setw(42) << "Guardar y salir" << endl;
		if (opcion == 3)
			cout << setw(35) << "-->" << setw(7) << "Cargar Partidas" << endl;
		else
			cout << setw(41) << "Cargar Partidas" << endl;
		if (opcion == 4)
			cout << setw(35) << "-->" << setw(7) << "Salir sin guardar" << endl;
		else
			cout << setw(42) << "Salir sin guardar" << endl;
		accion = leeAccion();
	}

	return opcion;
}

void fInstrucciones(string nombre){
				
	ifstream archivo;
	archivo.open(nombre);
	string texto;
	if (archivo.is_open()) {
		while (!archivo.fail()) {
			getline(archivo, texto);
			cout << texto << endl;
		}
		archivo.close();
	}
	else
		cout << "¡No se puede abrir el archivo!" << endl;			
}


// cout << setw(41) << "Nueva Partida" << endl; if (accion != Esc)
		//		crearTabla(v, casillas, puntos, totalpuntos);