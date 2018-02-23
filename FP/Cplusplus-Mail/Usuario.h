#ifndef Usuario_h
#define Usuario_h

#include "ListaRegistros.h"
#include <string>

using namespace std;

const string CENT_USER="X";
const string CENTINELA_LISTA = "XXX";

typedef struct {
	string nombre;
	string contrase�a;
	tListaRegistros listaRecibidos;
	tListaRegistros listaEnviados;
}tUsuario;

namespace usuario {
	bool cargar (tUsuario & usuario, ifstream & archivo);
	void guardar (const tUsuario & usuario, ofstream & archivo);
}

void inicializar (tUsuario & usuario, string id, string contrase�a);
bool validarContrase�a (const tUsuario & usuario, string contrase�a);

#endif