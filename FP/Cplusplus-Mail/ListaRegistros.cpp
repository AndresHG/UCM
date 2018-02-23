#include "ListaRegistros.h" 


void listaRegistros::inicializar (tListaRegistros & listaReg) {
	listaReg.cont=0;
	listaReg.max=10;
	listaReg.lista = new tRegCorreoPtr [listaReg.max];
}

void listaRegistros::cargar (tListaRegistros &listaReg, ifstream & archivo) {
	tRegistroCorreo reg;
	archivo >> listaReg.cont;

	int max = listaReg.cont;
	while (max%10!=0)
		max++;
	listaReg.max = max;
	
	listaReg.lista = new tRegCorreoPtr[listaReg.max];

	
	int i=0;
	while (i<listaReg.cont && i < listaReg.max) {
		tRegistroCorreo *reg= new tRegistroCorreo;
		archivo >> reg->identificador;
		archivo >> reg->leido;
		listaReg.lista[i]=reg;
		i++;
	}
	
	ordenaXFecha(listaReg);
}

void listaRegistros::guardar (const tListaRegistros & listaReg, ofstream & archivo) {
	archivo << listaReg.cont << endl;
	
	int i=0;
	while (i<listaReg.cont) {
		archivo <<  listaReg.lista[i]->identificador << " " << listaReg.lista[i]->leido << endl;
		i++;
	}
}

int listaRegistros::buscar (const tListaRegistros & listaReg, string id) {
	int pos = -1;
	bool enc = false;


	for(int i=0; i < listaReg.cont; i++) {
		if(id==listaReg.lista[i]->identificador){
			enc=true;
			pos=i;
		}
	}
	return pos;
}

bool listaRegistros::insertar (tListaRegistros & listaReg, tRegistroCorreo & registro) {
	bool insertado;
	
	if(listaReg.cont>=listaReg.max) {	
		int nuevaCapacidad = (listaReg.cont*3)/2+1;
		tListaRegistros auxiliar;
		auxiliar.lista = new tRegCorreoPtr [listaReg.cont];
		for(int i=0;i<listaReg.cont;i++){
			auxiliar.lista[i] = listaReg.lista[i];
		}
		delete [] listaReg.lista;
		listaReg.lista = new tRegCorreoPtr [nuevaCapacidad];
		listaReg.max=nuevaCapacidad;

		for(int i=0;i<listaReg.cont;i++){
			listaReg.lista[i]= auxiliar.lista[i];
		}
		delete [] auxiliar.lista;
	}

	listaReg.lista[listaReg.cont]=&registro;
	listaReg.cont++;
	insertado=true;
	
	ordenaXFecha(listaReg);
	return insertado;
}

bool borrar (tListaRegistros & listaReg, string id) {
	bool borrado;
	tRegistroCorreo aux;
	int pos=listaRegistros::buscar(listaReg, id);

	
	if(pos==-1 ){
		borrado=false;
	}
	else{
		int i=pos;
		while(i<=listaReg.cont-2) {
			listaReg.lista[i]=listaReg.lista[i+1];
			i++;
		}
		listaReg.cont--;
		borrado=true;
	}
	return borrado;
}

bool correoLeido (tListaRegistros & listaReg, string id) {
	int pos = listaRegistros::buscar(listaReg,id);
	bool leido;
	if (pos == -1){
		leido=false;
	}
	else {
		leido=true;
		listaReg.lista[pos]->leido=1;
	}
	return leido;
}

bool listaLleno(const tListaRegistros & listaC){
	bool lleno;
	if (listaC.cont >= listaC.max)
			lleno = true;
	else 
		lleno = false;
	
	return lleno;
}

void ordenaXFecha (tListaRegistros & listaReg) {
	tRegistroCorreo auxiliar;
	string senya = "_";
	string fecha1, fecha2, enc;
	int pos;

	for(int i=0;i<listaReg.cont;i++) {
		for(int j=i;j<listaReg.cont;j++) { 
			pos = listaReg.lista[j]->identificador.rfind(senya);
			fecha1 = listaReg.lista[j]->identificador.substr(pos+1,listaReg.lista[j]->identificador.size());
			pos = listaReg.lista[i]->identificador.rfind(senya);
			fecha2 = listaReg.lista[i]->identificador.substr(pos+1,listaReg.lista[i]->identificador.size());

			if(fecha1 > fecha2){
				tRegistroCorreo *auxiliar = new tRegistroCorreo;
				auxiliar=listaReg.lista[j];
				listaReg.lista[j]=listaReg.lista[i];
				listaReg.lista[i]=auxiliar;
			}
		}
	}
}