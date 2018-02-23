#include "Usuario.h"

bool usuario::cargar (tUsuario & usuario, ifstream & archivo) {
	bool ok = false;
	//Comprobamos que el nombre a cargar no sea el centinela
	string txt;
	archivo >> txt;
	if(txt != CENTINELA_LISTA) {
		usuario.nombre = txt;
		archivo >> usuario.contrase�a;
		listaRegistros::cargar(usuario.listaRecibidos, archivo); 
		listaRegistros::cargar(usuario.listaEnviados, archivo);
		ok = true;
	}
	return ok;
}

void usuario::guardar(const tUsuario & usuario, ofstream & archivo){
	archivo << usuario.nombre << endl;
	archivo << usuario.contrase�a << endl;

	listaRegistros::guardar(usuario.listaRecibidos,archivo);
	listaRegistros::guardar(usuario.listaEnviados, archivo);
}

void inicializar (tUsuario & usuario, string id, string contrase�a) {
	
	usuario.nombre= id;
	
	usuario.contrase�a=contrase�a;//Validamos contrase�a
	listaRegistros::inicializar(usuario.listaRecibidos);
	listaRegistros::inicializar(usuario.listaEnviados);
}

bool validarContrase�a (const tUsuario & usuario, string contrase�a){
	bool okey;

	if(usuario.contrase�a==contrase�a)
		okey=true;
	else
		okey=false;

	return okey;
}