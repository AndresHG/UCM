#ifndef ListaUsuario_h
#define ListaUsuario_h

#include "Usuario.h"
#include <iostream>
#include <sstream>

using namespace std;

const int MAX_USUARIO = 50;

typedef struct {
	tUsuario*lista[MAX_USUARIO];
	int cont;
}tListaUsuarios;

namespace listaUsuarios {
	void inicializar (tListaUsuarios & usuarios);
	bool cargar (tListaUsuarios & usuarios, string dominio);
	void guardar (const tListaUsuarios & usuarios, string dominio);
}

bool anyadir (tListaUsuarios & usuarios, const tUsuario & usuario);
bool buscarUsuario (const tListaUsuarios & usuarios, string id, int & posicion);

#endif