
/* Andrés Herranz González 
Guillermo Rius García 
Facultad de Informatica 1º D
Universidad Complutense de Madrid
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

int const CENTINELA=53;
int const CARTASPALO=13;
int const MAXCARTAS=52;

typedef int tCarta;
typedef enum {picas, treboles, diamantes, corazones} tPalo;
typedef enum {As, dos, tres, cuatro, cinco, seis, siete, ocho, nueve, diez, J, Q, K} tNumero;
typedef tCarta tMazo[MAXCARTAS];

void crearMazoVacio(tMazo mazo);
int cuantasEnMazo(const tMazo mazo);
tPalo darPalo(tCarta carta);
tNumero darNumero(tCarta carta);
void escribirCarta(tCarta carta);
void escribirMazo(tMazo mazo);
bool cargarMazo(tMazo mazo);
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);
void barajarMazo(tMazo mazo);
void cortarMazo(tMazo mazo, int cuantas);
void guardarMazo(const tMazo mazo);
void trucoTresMontones();
void igualarMazos(tMazo mazoAux, tMazo mazoOrigen);
int darNumNumerico(tCarta carta);
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);
void repartirEnTres (tMazo mazo);
int fMenu(int opcion);
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void trucoPosada();

int main() {

	int opcion=0;
	bool valido = false;
	tMazo mazo;
	tMazo mazoRojo, mazoNegro;
	tMazo mazoAltas, mazoBajas;
	crearMazoVacio(mazo);
	locale::global(locale("spanish"));
	srand(time(NULL));
	
	cout << "¡Bienvenido al simulador de trucos de magia!" << endl;
	opcion = fMenu(opcion);
	cout << endl;
	while (opcion != 0){
		switch (opcion){
			case (1):
				valido = false;

				cout << "-----------------------------CARGAR MAZO -----------------------------" << endl;
				if (mazo[0] != CENTINELA)
					cout << "Las cartas antes cargadas se perderan" << endl;
				for (int i=0; i<3 && !valido; i++)
					valido = cargarMazo(mazo);
				if (valido){
					cout << "El mazo se cargó correctamente" << endl;
					escribirMazo(mazo);
				}
				cout << endl;
				break;

			case (2):
				cout << "-----------------------------BARAJAR MAZO -----------------------------" << endl;
				barajarMazo(mazo);
				break;

			case (3):
				cout << "-----------------------------AÑADIR MAZO -----------------------------" << endl;
				tMazo mazoAgregar;
				int cM, cA;
				valido=false;
				crearMazoVacio(mazoAgregar);

				if (mazo[0] != CENTINELA){
					for (int i=0; i<3 && !valido; i++)
						valido = cargarMazo(mazoAgregar);
					cM = cuantasEnMazo(mazo);
					cA = cuantasEnMazo(mazoAgregar);
					if (valido && cA+cM < MAXCARTAS){
						cout << "El mazo se agregó correctamente" << endl << endl;
						unirMazos(mazo, mazoAgregar);
						escribirMazo(mazo);
					}
					else
						cout << "El mazo no se pudo añadir correctamente por algun problema ageno al mago (o que habia mas de 51 cartas)" << endl;
				}
				else
					cout << "Debe cargar un mazo antes" << endl;
				break;

			case (4):
				cout << "-----------------------------CORTAR MAZO -----------------------------" << endl;
				int cuantas;

				cout << "¿En cuantas desea cortar el maszo? ";
				cin >> cuantas;
				cout << endl;
				if (cuantas >= cuantasEnMazo(mazo) || cuantas < 0)
					cout << "No se pudo cortar el mazo" << endl;
				else{
					cortarMazo(mazo, cuantas);
					escribirMazo(mazo);
				}
				break;

			case (5):
				cout << "-----------------------------GUARDAR MAZO -----------------------------" << endl;
				if (mazo[0] != CENTINELA)
					guardarMazo(mazo);
				else
					cout << "No hay ningun mazo que guardar" << endl;
				cout << endl;
				break;

			case (6):
				cout << "----------------------------DIVIDIR MAZO NEGRO ROJO ---------------------------" << endl;
				crearMazoVacio(mazoRojo);
				crearMazoVacio(mazoNegro);

				if (mazo[0] < CENTINELA){
					repartirNegroRojo(mazo, mazoNegro, mazoRojo);
					cout << "El mazo ROJO es: " << endl;
					escribirMazo(mazoRojo);
					cout << endl << endl;
					cout << "El mazo NEGRO es: " << endl;
					escribirMazo(mazoNegro);
				}
				else
					cout << "No hay cartas en el mazo" << endl;
				break;

			case (7):
				cout << "----------------------------DIVIDIR MAZO ALTAS BAJAS ---------------------------" << endl;
				crearMazoVacio(mazoAltas);
				crearMazoVacio(mazoBajas);
				if (mazo[0] < CENTINELA){
					repartirBajaAlta(mazo, mazoBajas, mazoAltas);
					cout << "El mazo con las cartas ALTAS es: " << endl;
					escribirMazo(mazoAltas);
					cout << endl << endl;
					cout << "El mazo con las cartas BAJAS es: " << endl;
					escribirMazo(mazoBajas);
				}
				else
					cout << "No hay cartas en el mazo" << endl;
				break;

			case (8):
				cout << "-----------------------------REPARTIR MAZO EN 3 -----------------------------" << endl;
				repartirEnTres (mazo);
				break;

			case (9):
				cout << "-----------------------------TRUCO TRES MONTONES -----------------------------" << endl;
				trucoTresMontones();
				break;

			case (10):
				cout << "-----------------------------TRUCO POSADA -----------------------------" << endl;
				trucoPosada();
				break;

			case (11):
				ifstream archivo;
				archivo.open("Hola.txt");
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
				break;
		}
		cout << endl;
		opcion = fMenu(opcion);
		cout << endl;
	}
	system("pause");
}

int fMenu(int opcion){  // Nos permite escoger la opción que queramos.

	cout << "1.- Cargar nazo" << endl;
	cout << "2.- Barajar mazo" << endl;
	cout << "3.- Añadir mazo" << endl;
	cout << "4.- Cortar mazo" << endl;
	cout << "5.- Guardar mazo" << endl;
	cout << "6.- Separar en negras y rojas" << endl;
	cout << "7.- Separar en bajas y altas" << endl;
	cout << "8.- Repartir un mazo de manera alterna en 3 montones" << endl;
	cout << "9.- Truco tres montones" << endl;
	cout << "10.- Truco de la posada" << endl;
	cout << "11.- Instrucciones de uso" << endl;
	cout << "0 para salir" << endl;
	cout << "Escriba su opcion <1-11>:  ";
	cin >> opcion;
	while(opcion < 0 || opcion > 11){
		cout << "Error, choose again: ";
		cin >> opcion;
	}
	return opcion;
}

void crearMazoVacio(tMazo mazo){ // Creamos un mazo que no contiene ninguna carta y en el cual introducimos el centinela en la primera posición.
	mazo[0]=CENTINELA;
}

int cuantasEnMazo(const tMazo mazo){ // Va contando las cartas hasta que encuentra el centinela y nos devuelve el numero de cartas que hay en el mazo.

	int contador=0;
	while (mazo[contador] < CENTINELA){
		contador++;
	}
	return contador;
}

tPalo darPalo(tCarta carta){ // Determinamos el palo al que pertenece la carta que recibe como parametro y devolvemos el palo como tPalo.

	tPalo palo;
	int x;
	x= carta/CARTASPALO;

	if (x==0)
		palo = picas;
	else if (x==1){
		palo= treboles;
		if ((carta % CARTASPALO) == 0)
			palo= picas;
	}
	else if (x==2){
		palo= diamantes;
		if ((carta % CARTASPALO) == 0)
			palo= treboles;
	}
	else if (x==3){
		palo= corazones;
		if ((carta % CARTASPALO) == 0)
			palo= diamantes;
	}
	else if (x==4)
		palo= corazones;

	return palo;
}

string darStringPalo(tCarta carta){ // Función auxiliar que creamos para que nos sea más facil la escritura en pantalla.

	string palostr;
	tPalo palo;

	switch(palo=darPalo(carta)){
		case picas: palostr = "picas";			break;
		case treboles: palostr = "treboles";	break;
		case diamantes: palostr = "diamantes";	break;
		case corazones: palostr = "corazones";	break;
	}
	return palostr;
}

tNumero darNumero(tCarta carta) { /* Determinamos el numero de la carta, que recibe como parametro de entrada, dentro de su palo  
									y devolvemos el numero como tNumero */

	tNumero numero;

	switch (carta % CARTASPALO) {
		case (0): numero = As;		break;
		case (1): numero = dos;		break;
		case (2): numero = tres;	break;
		case (3): numero = cuatro;	break;
		case (4): numero = cinco;	break;
		case (5): numero = seis;	break;
		case (6): numero = siete;	break;
		case (7): numero = ocho;	break;
		case (8): numero = nueve;	break;
		case (9): numero = diez;	break;
		case (10) :numero = J;		break;
		case (11): numero = Q;		break;
		case (12): numero = K;		break;
	}
	return numero;
}

void escribirCarta(tCarta carta){ // Esta función simplemente muestra por pantalla el número y el palo de la carta que entra como parámetro

	cout << darNumNumerico(carta) << " de " << darStringPalo(carta) << endl;
}

void escribirMazo(tMazo mazo){ /* Esta función muestra por pantalla el contenido del mazo llamando
	                           a la función anterior y mostrando una a una las cartas del mazo de entrada*/
	tCarta carta;
	int x=0;

	while (mazo[x] < CENTINELA){
		carta = mazo[x];
		escribirCarta(carta);
		x++;
	}
}

bool cargarMazo(tMazo mazo){ // Carga un mazo de un archivo de texto, cargará cartas hasta que encuentre el centinela 'x' o hasta un max de 52 cartas.

	ifstream archivo;
	bool valido;
	char x='a';
	int y=0, puesto=0;
	tCarta elemento;
	string nomMazo;

	cout << "Introduce el nombre del archivo: ";
	cin >> nomMazo;
	archivo.open(nomMazo);
	if (archivo.is_open()){ // Comprobamos si se ha abierto correctamente el archivo.
		while (x!='x'){
			if (puesto < MAXCARTAS){
				archivo >> x;
				archivo >> y;
				if (x=='p')
					elemento=y;
				else if (x=='t')
					elemento= CARTASPALO + y;
				else if (x=='d')
					elemento= 2 * CARTASPALO + y;
				else if (x=='c')
					elemento= 3 * CARTASPALO + y;
				mazo[puesto]= elemento;
				puesto++;
			}
			else {
				x='x';
			}
		}
		mazo[puesto-1] = CENTINELA;
		(archivo.close());
		valido=true;
	}
	else {
		cout << "Fallo al abrir el archivo" << endl;
		valido=false;
	}
	return valido;
}

void barajarMazo(tMazo mazo){ /* Hace el numero de cartas en el mazo * 3 intercambios de cartas, ayudandonos de un aux y dos valores 'aleatorios' 
							  intercambiamos las cartas que se corresponden con dichos 'aleatorios' entre si*/
	int ncartas=0, x, y, valor1;
	ncartas= (cuantasEnMazo(mazo) - 1);
	if (cuantasEnMazo(mazo) > 0) {
		for (int i=1; i <= (cuantasEnMazo(mazo)*3); i++){
			x = rand() % ncartas;
			y = rand() % ncartas;
			while (y==x)
				y = rand() % ncartas;
			valor1 = mazo[x];
			mazo[x] = mazo[y];
			mazo[y] = valor1;
		}
		cout << "El mazo se barajo correctamente" << endl << endl;
		escribirMazo(mazo);
	}
	else
		cout << "No hay cartas que barajar, cargue primero un mazo" << endl;
}

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo) {

	bool valido;
	int numorigen, numnuevo, h=0;
	numorigen = cuantasEnMazo(mazoOriginal);
	numnuevo = cuantasEnMazo(nuevoMazo);

	if((numorigen + numnuevo) <= MAXCARTAS){
		for(int i=numorigen; i <= (numorigen + numnuevo); i++){
			mazoOriginal[i] = nuevoMazo[h];
			h++;
		}
		valido = true;
	}
	else {
		valido=false;
		cout << "Se ha superado el limite máximo de cartas por mazo" << endl;
	}
	//numorigen = cuantasEnMazo(mazoOriginal);
	//mazoOriginal[numorigen] = CENTINELA;
	return valido;
}

bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino){ /* función a la cual entran dos mazos y un entero como parámetros; este último será el numero de cartas que cogemos para partir el mazo.
																		Para esto modificaremos los dos mazo: en el primero quedarán las cartas que no hemos cogido y en el segundo el número de cuantasCoger. 
																		Logicamente	el valor de cuantasCoger ha de ser menor que el numero de cartas en el mazo origen*/
	int h=0, i=0;
	int l=0;
	l = cuantasEnMazo(mazoOrigen);
	bool valido;

	if (cuantasCoger <= l) {
		while (i < cuantasCoger){ 
			mazoDestino[i] = mazoOrigen[i];
			i++;
		}
		mazoDestino[i] =  CENTINELA;
		for (int x = cuantasCoger; x <= l; x++) {
			mazoOrigen[h] = mazoOrigen[x];
			h++;
			// Con este bucle for tambien estamos transladando la posicion del centinela.
		}
		// En mazoDestino, no  estaba puesto el CENTINELA todavia.
		valido = true;
	}
	else {
		valido = false;
		crearMazoVacio(mazoDestino);
	}
	return valido;
}

void cortarMazo(tMazo mazo, int cuantas) { // Coge el numero de cartas "cuantas" y las coloca al final utilizando las funciones partirMazo y unirMazos.

	tMazo nuevoMazo;
	crearMazoVacio(nuevoMazo);
	
	if (cuantas >= cuantasEnMazo(mazo) || cuantas < 0)
		cout << "No se pudo cortar el mazo" << endl;
	else {
		partirMazo(mazo, cuantas, nuevoMazo); 
		unirMazos(mazo, nuevoMazo);
	}
}

char darInicialPalo(tCarta carta){ /* Función aux que nos devuelve la inicial del palo de la carta 
	                                que recibe como parámetro, nos será util a la hora de guardar el mazo*/

	char inicial;

	switch (carta/CARTASPALO) {
		case (0): inicial = 'p';	break;
		case (1): inicial = 't';	break;
		case (2): inicial = 'd';	break;
		case (3): inicial = 'c';	break;
		case (4): inicial = 'c';	break;
	}
	return inicial;
}

int darNumNumerico(tCarta carta){ /* Función aux que nos devuelve el valor numerico de la carta 
	                                que recibe como parámetro, nos será util a la hora de guardar el mazo*/

	int numerico;

	switch (carta % CARTASPALO) {
		case (0): numerico = 13;		break;
		case (1): numerico = 1;		    break;
		case (2): numerico = 2;			break;
		case (3): numerico = 3;			break;
		case (4): numerico = 4;			break;
		case (5): numerico = 5;			break;
		case (6): numerico = 6;			break;
		case (7): numerico = 7;			break;
		case (8): numerico = 8;			break;
		case (9): numerico = 9;			break;
		case (10): numerico = 10;		break;
		case (11): numerico = 11;		break;
		case (12):numerico = 12;		break;
	}
	return numerico;
}

void guardarMazo(const tMazo mazo){ // Guarda el mazo que queramos en un archivo de tal manera que después podamos leerlo.

	ofstream registro;
	string nomarchivo;
	tCarta carta;

	cout << "Especifique el nombre del archivo del archivo en el que quieres guardar el mazo acabado en .txt:  "; // Es necesario especificar el tipo de archivo.
	cin >> nomarchivo;
	cout << endl;

	registro.open(nomarchivo);

	if(cuantasEnMazo(mazo) != 0){
		if (registro.is_open()) {
			for (int i=0; i < cuantasEnMazo(mazo); i++){
				carta = mazo[i];
				registro << darInicialPalo(carta) << " " << darNumNumerico(carta) << endl;
			}
			registro << 'x';
			registro.close();
		}
	}
	else 
		cout << "Fallo en la escritura" << endl;
}

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo) { /* Separa las cartas del parámetro mazo en dos mazos, uno que contenga las cartas
																			negras otro que contenga las cartas rojas, que serán los otros dos parametros */
	int color, x=0, z=0;

	for (int i=0; mazo[i] < CENTINELA; i++){
		color = (mazo[i] / CARTASPALO);
		if (color == 0 || color == 1 || mazo[i]	== 26) {
			mazoNegro[x] = mazo[i];
			x++;
		}
		else {
			mazoRojo[z] = mazo[i];
			z++;
		}
	}
	mazoNegro[x]=CENTINELA;
	mazoRojo[z]=CENTINELA;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas){ /* Igual que en la función anterior el mazo del parámetro de entrada lo 
																		   dividirá en dos mazos diferentes pero esta vez en cartas Altas o Bajas*/
	int num, x=0, z=0;

	for (int i=0; mazo[i] < CENTINELA; i++){
		num = (mazo[i] % CARTASPALO);
		if (num <= 7 && num != 0){
			mazoBajas[x] = mazo[i];
			x++;
		}
		else {
			mazoAltas[z] = mazo[i];
			z++;
		}
	}
	mazoBajas[x]=CENTINELA;
	mazoAltas[z]=CENTINELA;
}

void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo){ 

	int x=0, aux=0;
	aux = cuantasEnMazo(mazo);

	for (int i=0; i <= aux; i++){
		if (i == (queMazoPido - 1)){
			mazoNuevo[x] = mazo[i];
			queMazoPido = queMazoPido + enCuantosMazos;
			x++;
		}
	}
	mazoNuevo[x] = CENTINELA;
}

void igualarMazos(tMazo mazoAux, tMazo mazoOrigen){
	int i = 0;
	while (mazoAux[i] != CENTINELA){
		mazoOrigen[i] = mazoAux[i];
		i++;
	}
	mazoOrigen[i] = mazoAux[i];
}

void repartirEnTres (tMazo mazo) {

	tMazo mazoDividido;
	crearMazoVacio (mazoDividido);

	if (mazo[0] < CENTINELA){
		/*cout << "Mazo origen: " << endl;
		escribirMazo(mazo);
		cout << endl;*/
		repartirIntercalando(mazo,3,1,mazoDividido);
		cout << "Primer mazo: " << endl;
		escribirMazo (mazoDividido);
		cout << endl;
		repartirIntercalando(mazo,3,2,mazoDividido);
		cout << "Segundo mazo: " << endl;
		escribirMazo(mazoDividido);
		cout << endl;
		repartirIntercalando(mazo,3,3,mazoDividido);
		cout << "Tercer mazo: " << endl;
		escribirMazo(mazoDividido);
		cout << endl;
	}
	else
		cout << "No hay cartas en el mazo" << endl;
}

void trucoTresMontones(){

	tMazo mazoTruco;
	tMazo mazo1, mazo2, mazo3;
	int x;
	crearMazoVacio(mazoTruco);
	cargarMazo(mazoTruco);
	cout << endl;
	while (cuantasEnMazo(mazoTruco) != 21){
		cout << "El mazo cargado no tenia 21 cartas, por favor elija uno que si las tenga" << endl;
		crearMazoVacio(mazoTruco);
		cargarMazo(mazoTruco);
	}
	barajarMazo(mazoTruco);
	cout << endl;
	cout << "Elija una carta, pero no me la diga " << endl;
	cout << endl;

	for (int i=0; i < 3; i++) {
		repartirIntercalando(mazoTruco, 3, 1, mazo1);
		repartirIntercalando(mazoTruco, 3, 2, mazo2);
		repartirIntercalando(mazoTruco, 3, 3, mazo3);

		cout << "Mazo 1" << endl; escribirMazo(mazo1); 
		cout << endl << "Mazo 2" << endl; escribirMazo(mazo2);
		cout << endl << "Mazo 3" << endl; escribirMazo(mazo3);
		cout << endl << "Escriba en que mazo se encuentra su carta: ";
		cin >> x;
		while (x < 1 || x > 3){
			cout << "Debe elegir un mazo entre 1 y 3: ";
			cin >> x;
		}
		cout << endl;

		switch (x){
		case (1): 
			unirMazos(mazo2, mazo1);
			unirMazos(mazo2, mazo3);
			igualarMazos(mazo2, mazoTruco);
			break;
		case (2): 
			unirMazos(mazo1, mazo2);
			unirMazos(mazo1, mazo3);		
			igualarMazos(mazo1, mazoTruco);
			break;
		case (3):
			unirMazos(mazo1, mazo3);
			unirMazos(mazo1, mazo2);
			igualarMazos(mazo1, mazoTruco);
			break;			 
		}

	}
	cout << "La carta que usted ha elegido es: ";
	escribirCarta(mazoTruco[10]);
	cout << endl;
}

void trucoPosada(){

	tMazo mazoPosada, mazoAux, mazoResult;
	bool valido=false;
	int numHabitas = 4, intentos=0, cualCortar;
	crearMazoVacio(mazoResult);
	crearMazoVacio(mazoPosada);

	while (!valido && intentos !=3){
		valido = cargarMazo(mazoPosada);
		intentos++;
	}
	if (valido && (cuantasEnMazo(mazoPosada) == 16)) {
		for (int i=0; i < numHabitas; i++) {
			cout << endl;
			cout << "Habitación: " << i+1 << endl;
			repartirIntercalando(mazoPosada, 4, i+1, mazoAux);
			escribirMazo(mazoAux);
			unirMazos(mazoResult, mazoAux);
		}
		cout << "Elija la carta entre el 1 y 16 por la cual desea cortar el mazo: ";
		cin >> cualCortar;
		cout << endl;
		while (cualCortar < 1 && cualCortar > 16) {
			cout << "Error. Elija una entre el 1 y 16: ";
			cin >> cualCortar;
			cout << endl;
		}
		cortarMazo(mazoResult, cualCortar);
		cout << "A la mañana siguiente..." << endl;
		for (int i = 0; i < numHabitas; i++) {
			cout << "Habitación: " << i+1 << endl;
			repartirIntercalando(mazoResult, 4, i+1, mazoAux);
			escribirMazo(mazoAux);
			cout << endl;
		}
	}
	else
		cout << "Lo siento, el mazo debe tener 16 cartas en el orden indicado en la instrucciones" << endl;
}


/* FIN */