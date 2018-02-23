#ifndef Gestor_h
#define Gestor_h

#include <string>
#include <conio.h>
#include <Windows.h>
#include "ListaCorreos.h"
#include "ListaUsuarios.h"
#include "ListaRegistros.h"


using namespace std;

typedef struct {
	string dominio;
	tListaCorreos listaCorreos;
	tListaUsuarios listaUsuarios;
	int activo; 

}tGestor;

bool arrancar (tGestor & gestor, string dominio);
void apagar (const tGestor & gestor);
bool crearCuenta (tGestor & gestor);
bool iniciarSesion ( tGestor & gestor);
void leerCorreo (tGestor & gestor, tListaRegistros & listaReg);
void enviarCorreo (tGestor & gesotr, const tCorreo & correo);
void borrarCorreo (tGestor & gestor, tListaRegistros & listaReg);

void mostrarNoLeidos (tGestor & gestor,tListaRegistros & listaReg);
void lecturaRapida (tGestor & gestor, tListaRegistros & listaReg);

#endif