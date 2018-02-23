#include "ListaUsuarios.h"


void listaUsuarios::inicializar (tListaUsuarios & usuarios) {
	usuarios.cont=0;
}

bool listaUsuarios::cargar (tListaUsuarios & usuarios, string dominio) {
	ifstream archivo;
	stringstream flujo;
	bool ok;

	string dir;
	flujo << dominio << "_Usuarios.txt";
	dir=flujo.str();
	archivo.open(dir);
	
	tUsuario *aux;
	if(!archivo.is_open()) {
		ok=false;
	}else {
		bool cargando=true;
		int i =0;
		while(cargando && i < MAX_USUARIO){
			aux = new tUsuario;
			cargando=usuario::cargar(*aux,archivo);
			if(cargando) {
				usuarios.lista[i]=aux;
				usuarios.cont++;
				i++;
			}
		}
		archivo.close();
		ok=true;	
	}
	return ok;
}

void listaUsuarios::guardar (const tListaUsuarios & usuarios, string dominio) {

	stringstream flujo;
	flujo << dominio << "_usuarios.txt";
	string dir= flujo.str();

	ofstream archivo;
	archivo.open(dir);

	tUsuario *aux;
	for(int i =0; i<usuarios.cont;i++) {
		aux = usuarios.lista[i];
		usuario::guardar (*aux, archivo);
	}
	archivo << CENTINELA_LISTA;
	archivo.close();
}

bool anyadir (tListaUsuarios & usuarios, const tUsuario & usuario) {
	bool ok;
	int pos;

	bool existe = buscarUsuario(usuarios, usuario.nombre, pos);
	if(existe) {
		ok=false;
	}
	else {
		tUsuario *aux= new tUsuario;
		*aux=usuario;
		if(usuarios.cont< MAX_USUARIO) { 
			int i = usuarios.cont;
			if(i==pos) {
				*aux=usuario;
				usuarios.lista[pos]=aux;
			}else{
			while (i>pos) {
				
				usuarios.lista[i]=usuarios.lista[i-1];
				i--;
			}
			usuarios.lista[pos]=aux;
			}
			usuarios.cont++;
			ok=true;
		}
	}
	return ok;
}

bool buscarUsuario (const tListaUsuarios & usuarios, string id, int & posicion) {
	bool encontrado=false;
	
	int i=0;
	while (!encontrado && i < usuarios.cont){
			if(usuarios.lista[i]->nombre == id) {
				encontrado = true;
				posicion = i;
			}
			i++;
	}

	if(i == usuarios.cont && !encontrado) {
		int j=0;
		while(j<i && id>usuarios.lista[j]->nombre){
			j++;
		}
		posicion = j;
	}
	return encontrado;
}
