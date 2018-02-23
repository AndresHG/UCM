/*
Facultad de Informática
Ingeniería Informática
UCM

Autore: 
	Andrés Herranz Gonzalez
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>

#include "ListaCorreos.h"
#include "ListaUsuarios.h"
#include "ListaRegistros.h"
#include "Gestor.h"

using namespace std;

const string DOMINIO = "fdimail.com";

int menuPrincipal ();
int menuBandeja(tGestor & gestor);
void cerrarSesion(tGestor & gestor);
int menuBandejaSalida(tGestor & gestor);

int main () {
	tGestor gestor;
	arrancar(gestor, DOMINIO);
	
	int op;
	op = menuPrincipal();
	
	//confirmar la sesion
	bool sesion,cuenta;
	while(op !=0){
		system("cls");
			switch (op) {
				case(1): 
					sesion = iniciarSesion(gestor);
					
					//Si inicia correctamente entra en la bandeja de entrada
					if(sesion){
						system("cls");
						for (int w=0;w<3;w++){
							for (int i=0;i<10;i++)
								cout << endl;
								cout << setw(46) << "Iniciando Sesion.";
								Sleep(750);
								for (int v=0;v<2;v++){
									cout << ".";
									Sleep(700);
								}
								system("cls");
						}
						
						int opcion = menuBandeja(gestor);
						while (opcion != 0)
							opcion = menuBandeja(gestor);
						system("cls");
						for (int w=0;w<3;w++){
							for (int i=0;i<10;i++)
								cout << endl;
							cout << setw(46) << "Cerrando Sesion.";
							Sleep(750);
							for (int v=0;v<2;v++){
								cout << ".";
								Sleep(700);
							}
							system("cls");
						}
					}
					cerrarSesion(gestor);
					system("cls");
					break;
				case(2):
					cuenta = crearCuenta(gestor);

					//Si se crea correctamente entra en la bandeja de entrada.
					if (cuenta){
						system("cls");
						op = menuBandeja(gestor);
						while (op != 0)
							op = menuBandeja(gestor);
						system("cls");
						for (int w=0;w<3;w++){
							for (int i=0;i<10;i++)
								cout << endl;
							cout << setw(46) << "Cerrando Sesion.";
							Sleep(750);
							for (int v=0; v<2; v++){
								cout << ".";
								Sleep(700);
							}
							system("cls");
						}
					}
					cerrarSesion(gestor);
					system("cls");
					break;
			}
			op = menuPrincipal();
			
			//Apagamos
			if(op==0){
				cout << "Guardando datos de USUARIOS y CORREOS" << endl;
				apagar(gestor);
				cout << endl << "GUARDADO CON EXITO" << endl;
			}
	}
	Sleep(2000);
	system("cls");
	return 0;
}

int menuPrincipal () {
	int op;
	cout << "Elija la opción deseada: " << endl;
	cout << "1- Acceder a mi cuenta de correo" << endl;
	cout << "2- Crear cuenta" << endl;
	cout << "0- Salir" << endl;
	cout << "Opción: ";
	cin >> op;
	return op;
}

int menuBandeja(tGestor & gestor) {
	int activo = gestor.activo;
	int recibidos= gestor.listaUsuarios.lista[activo]->listaRecibidos.cont;

	system("cls");

	cout << "Correo de " << gestor.listaUsuarios.lista[gestor.activo]->nombre << endl;
	cout << "--------------------------Bandeja de Entrada -------------------" << endl;
	cout << "----------------------------------------------------------------" << endl ;
	cout << "L-N " << setw(7) << "Emisor" << setw(25) << "Asunto" << setw(24) << "Fecha" << endl <<endl;
	cout << "----------------------------------------------------------------" << endl;
	
	//Obtenemos las cabeceras
	int pos;
	for (int i=0;i<recibidos;i++) {
		if(gestor.listaUsuarios.lista[activo]->listaRecibidos.lista[i]->leido==false)
			cout << "*";
		else
			cout << " ";
		
		//buscamos la pos del correo en la lista de correos.
		buscar(gestor.listaCorreos ,gestor.listaUsuarios.lista[activo]->listaRecibidos.lista[i]->identificador,pos);
		cout << setw(2) << i+1 << " - " << setw(3) << obtenerCabecera(*(gestor.listaCorreos.listaCorreos[pos])) << endl;
	}
	cout << "----------------------------------------------------------------" << endl;
	
	int opc;
	cout << "Elija una opción:" << endl;
	cout << 1 <<" - " <<  setw(5) << "Leer correo" << endl;
	cout << 2 <<" - " <<  setw(5) << "Enviar correo" << endl;
	cout << 3 <<" - " <<  setw(5) << "Borrar coreo" << endl;
	cout << 4 <<" - " <<  setw(5) << "Ver bandeja de Salida" << endl;
	cout << 5 <<" - " <<  setw(5) << "Lectura rapida de correos sin leer" << endl;
	cout << 0 <<" - " <<  setw(5) << "Cerrar sesión" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "Introduzca una opción: ";
	cin >> opc;

	//Se usa para enviar un correo nuevo.
	tCorreo aux;

	int out;

	switch (opc) {
		case(1):
			leerCorreo(gestor,  gestor.listaUsuarios.lista[gestor.activo]->listaRecibidos);
			break;

		case(2):
			correoNuevo(aux, gestor.listaUsuarios.lista[gestor.activo]->nombre);
			enviarCorreo(gestor,aux);
			break;

		case(3):
			borrarCorreo(gestor, gestor.listaUsuarios.lista[gestor.activo]->listaRecibidos);
			break;

		case(4):
			out = menuBandejaSalida(gestor);
			while(out!=4 && out!=0)
				out=menuBandejaSalida(gestor);
			if(out==0)
				opc=0;
			//Para cerrar Sesión
			break;

		case(5):
			//Lectura rapida de los mensaje.
			system("cls");
			mostrarNoLeidos(gestor,gestor.listaUsuarios.lista[gestor.activo]->listaRecibidos);
			cout << "----------------------------------------------------------------" << endl;
			cout << "Seguro que desea marcarlos como leidos? (Esc para salir)" << endl;
			int dir;
			cin.sync();
			dir = _getch();
			if (dir == 13){
				lecturaRapida(gestor,gestor.listaUsuarios.lista[gestor.activo]->listaRecibidos);
			}
			else {
				cout << "Se devolvieron a la bandeja de entrada" << endl;
				Sleep(2000);
			}		
			break;
	}	
	return opc;
}

void cerrarSesion(tGestor & gestor) {
	gestor.activo=-1;
}

int menuBandejaSalida(tGestor & gestor) {
	int activo = gestor.activo;
	int enviados= gestor.listaUsuarios.lista[activo]->listaEnviados.cont;
	
	system("cls");

	cout << "Correo de " << gestor.listaUsuarios.lista[gestor.activo]->nombre << endl;
	cout << "--------------------------Bandeja de Salida -------------------" << endl;
	cout << "----------------------------------------------------------------" << endl ;
	cout << "N " << setw(3) << "Emisor" << setw(20) << "Asunto" << setw(32) << "Fecha" << endl <<endl;
	cout << "----------------------------------------------------------------" << endl;
	
	//Obtenemos las cabeceras
	int pos=-1;
	for (int i=0;i < enviados; i++) {
		
		//buscamos la pos del correo en la lista de correos.
		buscar(gestor.listaCorreos, gestor.listaUsuarios.lista[activo]->listaEnviados.lista[i]->identificador, pos);
		if(pos != -1)
			cout << setw(2) << i+1 << " " << setw(4) << obtenerCabecera(*(gestor.listaCorreos.listaCorreos[pos])) << endl;
	}
	cout << "----------------------------------------------------------------" << endl;
	
	int opc;
	cout << "Elija una opción:" << endl;
	cout << 1 <<" - " <<  setw(5) << "Leer correo" << endl;
	cout << 2 <<" - " <<  setw(5) << "Enviar correo" << endl;
	cout << 3 <<" - " <<  setw(5) << "Borrar coreo" << endl;
	cout << 4 <<" - " <<  setw(5) << "Ver bandeja de Entrada" << endl;
	cout << 5 <<" - " <<  setw(5) << "Lectura rapida de correos sin leer" << endl;
	cout << 0 <<" - " <<  setw(5) << "Cerrar sesión" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "Introduzca una opción: ";
	
	cin >> opc;
	tCorreo aux;
	switch (opc) {
		case(1):
			leerCorreo(gestor, gestor.listaUsuarios.lista[gestor.activo]->listaEnviados);
			break;

		case(2):
			correoNuevo(aux, gestor.listaUsuarios.lista[gestor.activo]->nombre);
			enviarCorreo(gestor,aux);
			break;

		case(3):
			borrarCorreo(gestor, gestor.listaUsuarios.lista[gestor.activo]->listaEnviados);
			break;

		case(5):
		//Lectura rapida de los mensaje.
		lecturaRapida(gestor,gestor.listaUsuarios.lista[gestor.activo]->listaEnviados);
		break;
	}
	return opc;
}
