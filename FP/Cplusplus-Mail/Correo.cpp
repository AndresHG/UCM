#include "ListaCorreos.h"


void correoNuevo(tCorreo & ncorreo, string emisor) {
	stringstream flujo;

	typedef time_t tFecha;
	
	//Datos rellenos automaticamente
	ncorreo.fecha = time(0);
	ncorreo.emisor = emisor;
	flujo << emisor << "_" << ncorreo.fecha;
	ncorreo.identificador = flujo.str();

	//Pedimos los datos.
	cout << "Enviar un nuevo correo" << endl << endl;
	cout << "Destinatario: ";
	cin >> ncorreo.destinatario;  
	
	string txt;
	cout  << endl;
	getline(cin,txt);
	cout << "Asunto: ";
	getline(cin, ncorreo.asunto);

	cout  << endl;
	cout << "Mensaje: " << endl << endl;
	getline(cin, ncorreo.correo); //Extrae el correo
	
}

void correoContestacion (const tCorreo & correOriginal, tCorreo & correo, string emisor){ 
	typedef time_t tFecha;
	string asunto;
	correo.fecha = time(0);
	stringstream flujo;

	//Guardamos datos de emisor,asunto,receptor en mensaje contestacion
	correo.emisor =  correOriginal.destinatario;
	correo.destinatario = correOriginal.emisor;
	asunto = asuntoRe(correOriginal.asunto);
	flujo << "Re: " << asunto;
	correo.asunto = flujo.str();

	//Almacenamos el mensaje
	stringstream mensaje;
	string hola;
	cout << "Escribe el mensaje: " << endl;
	getline(cin, hola);
	getline (cin,correo.correo);
	mensaje << correo.correo << endl << "-----------------------------" << endl << correOriginal.correo;
	correo.correo = mensaje.str();

	stringstream ident;
	ident << correo.emisor << "_" << correo.fecha;
	correo.identificador = ident.str();
}


string aCadena (const tCorreo & correo) {
	stringstream flujo;
	string cadena;
	
	flujo << "De: " << correo.emisor;
	flujo << setw(30) << mostrarFecha(correo.fecha) << endl;
	flujo << "Para: " << correo.destinatario << endl;
	flujo << "Asunto: " << correo.asunto << endl << endl;

	flujo << correo.correo <<endl << endl;
	cadena = flujo.str();
	return cadena;
}


string obtenerCabecera (const tCorreo & correo) {
	string cabecera;
	stringstream flujo;
	string emisor,asunto,fecha;

	emisor= correo.emisor;
	asunto = correo.asunto; 
	fecha = mostrarFecha_SH(correo.fecha);
	
	if (emisor.length() > 18){
		emisor.erase(17, emisor.length());
		emisor.insert(17, "...");
		flujo << left << setw(25) <<emisor;
	}
	else
		flujo << left << setw(25) << emisor;

	if (asunto.length() > 18){
		asunto.erase(17, asunto.length());
		asunto.insert(17, "...");
		flujo << left << setw(25) << asunto;
	}
	else
		flujo << left << setw(25) << asunto;

	flujo << fecha; 
	cabecera = flujo.str();
	
	return cabecera;
}

bool correo::cargar (tCorreo & correo , ifstream & archivo) {
	bool cargado; //Resultado de cargar
	stringstream flujo;

	string id;
	archivo >> id;
	if(id == CENT_CORREO) {
		cargado= false;
	}
	else {
		string linea;
		correo.identificador = id;
		archivo >> correo.fecha;
		archivo >> correo.emisor;
		archivo >> correo.destinatario;
		getline(archivo,linea);
		getline(archivo,correo.asunto);
		//Almacenamos en un flujo todo el mensaje

		getline(archivo,linea);
		while (linea != CENT_CORREO) {
			flujo << linea;
			getline(archivo,linea);
			if(linea != CENT_CORREO)
				flujo << endl;
		}
		correo.correo = flujo.str();  //Almacenamos cuerpo del correo.
		cargado = true;
	}
	return cargado;
}

bool correo::guardar (const tCorreo & correo, ofstream & archivo){
	stringstream flujo;
	bool guardado = false;


	if(!archivo.is_open())
		cout << "No se ha podido abrir el archivo" << endl;
	else{
		archivo << correo.identificador << endl;
		archivo << correo.fecha << endl;
		archivo << correo.emisor << endl;
		archivo << correo.destinatario << endl;
		archivo << correo.asunto << endl;
		archivo << correo.correo << endl;
		archivo << CENT_CORREO << endl;
		guardado = true;
	}
	return guardado;

}

string mostrarFecha (tFecha fecha) {
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm,&fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1+ltm.tm_mon << "/" << ltm.tm_mday;
	resultado << " (" << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << ")";
	return resultado.str();
}

string mostrarFecha_SH (tFecha fecha) {
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm,&fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1+ltm.tm_mon << "/" << ltm.tm_mday;
	return resultado.str();
}