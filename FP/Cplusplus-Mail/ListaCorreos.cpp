#include "ListaCorreos.h"


void listaCorreos::inicializar (tListaCorreos & correos) {
	correos.cont = 0;
	correos.max = 10;
}

bool listaCorreos::cargar(tListaCorreos & correos, string dominio) {
	bool ok;
	
	ifstream archivo;
	stringstream flujo;
	flujo << dominio << "_correos.txt";
	string path = flujo.str();
	archivo.open(path);

	if(!archivo.is_open()) {
		ok=false;
	}else {
		archivo >> correos.cont;
		
		int max = correos.cont;
		while (max%10!=0)
			max++;
		correos.max = max;
		
		correos.listaCorreos = new tCorreoPtr[correos.max];
		
		bool cargando;
		for (int i =0;i<correos.cont;i++) {
			tCorreo *aux= new tCorreo;
			cargando = correo::cargar(*aux,archivo);
			
			correos.listaCorreos[i]=aux;
		}
		ok=true;
		archivo.close();
	}
		int x;
		if (correos.cont < correos.max)
			x = correos.cont;
		else
			x = correos.max -1;

	//Ordenar por el identificacdor
	tCorreo *auxiliar;
	for(int i=0;i<x;i++){
		for(int j=i;j<x;j++) {
			if(correos.listaCorreos[i]->identificador > correos.listaCorreos[j]->identificador) {
				auxiliar = correos.listaCorreos[i];
				correos.listaCorreos[i] = correos.listaCorreos[j];
				correos.listaCorreos[j] = auxiliar;
			}
		}
	}
	return ok;
}

void listaCorreos::guardar(const tListaCorreos & correos, string dominio) {
	ofstream archivo;
	stringstream flujo;
	flujo << dominio << "_correos.txt";
	string path = flujo.str();
	archivo.open(path);

	int i = 0;
	bool guardando = true;
	archivo << correos.cont << endl;

	while (guardando && i<correos.cont) {
		guardando = correo::guardar(*(correos.listaCorreos[i]),archivo);
		i++;
	}
	archivo.close();
}

bool listaCorreos::insertar (tListaCorreos & correos, const tCorreo & correo) {
	bool colocado;
	
	if(correos.cont==correos.max) {		
	
		int nuevaCapacidad = (correos.cont*3)/2+1;
		
		tListaCorreos auxiliar;
		auxiliar.listaCorreos = new tCorreoPtr [correos.cont];
		for(int i=0;i<correos.cont;i++){
			auxiliar.listaCorreos[i] = correos.listaCorreos[i];
		}
		
		delete [] correos.listaCorreos;
		correos.listaCorreos = new tCorreoPtr [nuevaCapacidad];
		correos.max=nuevaCapacidad;

		
		for(int i=0;i<correos.cont;i++){
			correos.listaCorreos[i]= auxiliar.listaCorreos[i];
		}
		delete [] auxiliar.listaCorreos;


	}
	int pos=0;
	while(pos < correos.cont && correos.listaCorreos[pos]->identificador < correo.identificador) {
		pos++;
	}

	for(int fin=correos.cont; fin > pos;fin--) {
		correos.listaCorreos[fin]=correos.listaCorreos[fin-1];
	}

	correos.listaCorreos[pos]=new tCorreo (correo); // 
	correos.cont++;
	colocado = true;

	return colocado;
	
}

bool buscar (const tListaCorreos & correos, string id, int & pos) {
	bool enc = false;
	
	int ini=0, fin=correos.cont-1, mitad;
	while(!enc && ini<=fin) {
		mitad = (ini+fin)/2;
		if(correos.listaCorreos[mitad]->identificador==id) {
			enc=true;
			pos=mitad;
		}else if(id < correos.listaCorreos[mitad]->identificador) {
			fin=mitad -1;
		}else if (id > correos.listaCorreos[mitad]->identificador) {
			ini=mitad +1;
		}
	}
	return enc;
}

void ordenar_AF (tListaCorreos & correos) {
	tCorreo *aux;

	for(int i=0; i<correos.cont; i++) {
		for(int j=i; j<correos.cont; j++) { 
			if(correos.listaCorreos[j] < correos.listaCorreos[i]){
				aux=correos.listaCorreos[j];
				correos.listaCorreos[j]=correos.listaCorreos[i];
				correos.listaCorreos[i]=aux;
			}
		}
	}
}



bool operator< (tCorreo correo1, tCorreo correo2) {
	bool resultado=false;
	string asunto1, asunto2;
	
	asunto1 = asuntoRe(correo1.asunto);
	asunto2 = asuntoRe(correo2.asunto);
	
	if(asunto1 < asunto2)
		resultado = true;
	if(asunto1 == asunto2) {
		if(correo1.fecha < correo2.fecha)
			resultado=true;
	}
	return resultado;
}


string asuntoRe(string asunto){
	size_t found=-1;

	found = asunto.find("Re: ");
	if (found !=- 1)
		asunto.erase (0,4);
	
	return asunto;
}