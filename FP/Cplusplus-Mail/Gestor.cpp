#include "Gestor.h"

bool arrancar (tGestor & gestor, string dominio) {
	ofstream archivo;
	stringstream flujo;
	string path1,path2;
	
	//Si falla la carga de una de los dos devolverá falso
	gestor.dominio = dominio;
	gestor.activo=-1;

	listaCorreos::inicializar(gestor.listaCorreos);
	listaUsuarios::inicializar(gestor.listaUsuarios);

	bool cLista,cCorreos;
	cLista = listaUsuarios::cargar(gestor.listaUsuarios,dominio);
	cCorreos = listaCorreos::cargar(gestor.listaCorreos,dominio);
	
	//En caso de que no exista el archivo, entra y lo crea.
	if(!cLista){
		flujo << dominio << "_Usuarios.txt";
		path1 = flujo.str();
		archivo.open(path1);
		archivo << CENTINELA_LISTA;
		flujo.str("");
		cout << "BASE DE DATOS DE USUARIOS CREADA..." << endl;
		archivo.close();
		cLista=true;
	}

	if(!cCorreos) {
		flujo << dominio << "_correos.txt";
		path2 = flujo.str();
		archivo.open(path2);
		archivo << gestor.listaCorreos.cont;
		gestor.listaCorreos.listaCorreos = new tCorreoPtr[10];
		cout << "BASE DE DATOS DE CORREOS CREADA..." << endl;
		archivo.close();
		cCorreos = true;
	}
	return cLista && cCorreos;
}

void apagar (const tGestor & gestor) {
	//Guardamos las listas de Usuario y Correos invocando sus funciones
	listaCorreos::guardar(gestor.listaCorreos,gestor.dominio);
	listaUsuarios::guardar(gestor.listaUsuarios, gestor.dominio);
}


bool crearCuenta (tGestor & gestor) {
	tUsuario nuevoUsuario;
	stringstream flujo;
	bool ok;
	string user, contraseña;
	int pos;
	cout << "Escribe un usuario: ";
	cin >> user;
	size_t found=-1;
	found = user.find("@fdimail.com");
	if (found == -1){
		flujo << user << "@fdimail.com";
		user = flujo.str();
	}

	//Comprobamos si existe el usuario
	bool user_igual= buscarUsuario(gestor.listaUsuarios, user, pos);
	if(user_igual) {
		cout << "Error, el usuario ya existe. " << endl;
		Sleep(2000);
		ok = false;
	}
	else if ( gestor.listaUsuarios.cont==MAX_USUARIO) {
		cout << "Error, la lista de Usuarios está llena" << endl;
		Sleep(2000);
		ok = false;
	}
	else {
		cout << "Escribe una contraseña: ";
		cin >> contraseña;
		
		//Inicializa y añade a la lista
		inicializar(nuevoUsuario, user, contraseña);
		anyadir(gestor.listaUsuarios, nuevoUsuario);
		buscarUsuario(gestor.listaUsuarios,nuevoUsuario.nombre,pos);
		gestor.activo=pos;
		ok=true;
	}
	return ok;
}


bool iniciarSesion ( tGestor & gestor) {
	bool ok;
	string user,pass;
	stringstream flujo;
	int pos;

	cout << "Escribe tu usuario: ";
	cin >> user;
	size_t found=-1;
	found = user.find("@fdimail.com");
	if (found == -1){
		flujo << user << "@fdimail.com";
		user = flujo.str();
	}
	cout << "Escribe la contraseña: ";
	cin >> pass;

	//Comprobamos si existe y coincide.
	if (buscarUsuario(gestor.listaUsuarios,user,pos) && validarContraseña(*(gestor.listaUsuarios.lista[pos]), pass)) {
		gestor.activo=pos;
		ok=true;
	}
	else {
		cout << "El usuario o contraseña no son Validos" << endl;
		Sleep(2000);
		ok=false;
	}
	return ok;
}

void leerCorreo (tGestor & gestor, tListaRegistros & listaReg) {
	int num,pos=-1,opc;
	
	//Pedimos el correo
	cout << "Introduce el numero de correo a leer: " <<endl;
	cin >> num;

	system("cls");
	if (num>0 && num-1 < listaReg.cont)
		pos= listaRegistros::buscar(listaReg,listaReg.lista[num-1]->identificador);

	if(pos != -1){
		//Marca como leido el correo.
		correoLeido(gestor.listaUsuarios.lista[gestor.activo]->listaRecibidos, listaReg.lista[pos]->identificador);
		buscar (gestor.listaCorreos, listaReg.lista[num-1]->identificador,pos);
		cout << aCadena(*(gestor.listaCorreos.listaCorreos[pos]));
	}

	else{
		cout << "El correo no se puede leer" << endl;
		system("pause");
	}
	
	

	if(pos==-1) {
		opc=0;
	}
	
	else{	
		cout << "---------------------------------------------------------------" << endl;
		cout << "Elija una opción: " << endl;
		cout << "1- Contestar al correo" << endl;
		cout << "0- Salir" << endl;
	
		do{
		cin >> opc;
		cin.clear();
		cin.sync();
		}while (opc != 1 && opc !=0);
	}
	
		switch(opc) {
			while(opc < 0 || opc > 1) {
				cout << endl << "Opcion Incorrecta:  ";
				cin >> opc;
			}
		case(1):
			tCorreo contCorreo;
			tRegistroCorreo *reg = new tRegistroCorreo;
			correoContestacion(*(gestor.listaCorreos.listaCorreos[pos]),contCorreo,gestor.listaUsuarios.lista[gestor.activo]->nombre);
			reg->identificador = contCorreo.identificador;
			reg->leido=false;
			int x;
			bool insert;
			if(gestor.listaCorreos.cont < gestor.listaCorreos.max && buscarUsuario(gestor.listaUsuarios,contCorreo.destinatario,x)){
				insert = listaRegistros::insertar(gestor.listaUsuarios.lista[x]->listaRecibidos, *reg);
				if(insert) {
					listaRegistros::insertar(gestor.listaUsuarios.lista[gestor.activo]->listaEnviados, *reg);
					listaCorreos::insertar(gestor.listaCorreos,contCorreo);
					cout << "Mensaje Enviado con Éxito" << endl;
				}
				else{
					cout << "El correo no se pudo enviar" << endl;
				}
			}
			else {
				cout << "El correo no se pudo enviar" << endl;
			}
			system("pause");
			break;
		}
}


void enviarCorreo (tGestor & gestor, const tCorreo & correo) {
	bool insertado;

	tRegistroCorreo *reg = new tRegistroCorreo;
	int pos_dest;

	if(buscarUsuario (gestor.listaUsuarios,correo.destinatario,pos_dest)) {		
		insertado = listaCorreos::insertar(gestor.listaCorreos,correo);
		
		if(insertado) {
			reg->identificador=correo.identificador;
			reg->leido = 1;
			listaRegistros::insertar(gestor.listaUsuarios.lista[gestor.activo]->listaEnviados, *reg);
			reg->leido = 0;

			if (gestor.listaUsuarios.lista[pos_dest]->listaRecibidos.cont <= gestor.listaUsuarios.lista[pos_dest]->listaRecibidos.max){
				listaRegistros::insertar(gestor.listaUsuarios.lista[pos_dest]->listaRecibidos, *reg);
				system("cls");
				for (int w=0;w<2;w++){
					for (int i=0;i<2;i++)
						cout << endl;
					cout << setw(46) << "Enviando Correo.";
					Sleep(750);
					for (int v=0;v<2;v++){
						cout << ".";
						Sleep(700);
					}
					system("cls");
				}
				for (int i=0;i<2;i++)
					cout << endl;
				cout << setw(47) << "Correo Enviado";
				Sleep(1500);
				system("cls");
			}
			else {
				cout << "El destinatario no recibira el correo, debido a que tiene la bandeja llena" << endl;
				Sleep(2000);
			}
		}
		else {
			cout << "Base de datos llena" << endl;
			Sleep(2000);
		}
	}
	else {
		cout << "El usuario no existe, el correo, no se envió" << endl;
		system("pause");
	}

}

void borrarCorreo (tGestor & gestor, tListaRegistros & listaReg) {
	bool ok, borrado;
	int num, pos;
	
	cout << "Que numero de correo desea borrar: " << endl;
	cin >> num;

	if (num-1 < listaReg.cont && num > 0 ) {
		bool enc = buscar (gestor.listaCorreos, listaReg.lista[num-1]->identificador , pos);
		if(enc)
			borrado = borrar(listaReg,gestor.listaCorreos.listaCorreos[pos]->identificador);

		if(borrado)
			cout << "El mensaje ha sido borrado con éxito" << endl;
		else
			cout << "No ha sido posible borrar el correo" << endl;
	}
	else 
		cout << "No ha sido posible borrar el correo" << endl;
	system("pause");
}

void lecturaRapida (tGestor & gestor,tListaRegistros & listaReg) {
	//Pasa los correos no leidos a leidos.
	for(int i=0;i<listaReg.cont;i++){
		if(listaReg.lista[i]->leido==0)
			listaReg.lista[i]->leido=1;
	}
}

void mostrarNoLeidos (tGestor & gestor,tListaRegistros & listaReg) {
	//Muestra los correos no leidos.
	tListaCorreos correos;
	correos.listaCorreos = new tCorreoPtr [gestor.listaCorreos.cont];
	correos.cont=0;

	int x =0, dir;
	cout << "Correos de " << gestor.listaUsuarios.lista[gestor.activo]->nombre << endl;
	cout << "--------------------------Bandeja de Entrada -------------------" << endl;
	cout << "----------------------------------------------------------------" << endl ;
	cout << "L-N " << setw(7) << "Emisor" << setw(25) << "Asunto" << setw(24) << "Fecha" << endl <<endl;
	cout << "----------------------------------------------------------------" << endl;
	for(int i=0;i<listaReg.cont;i++){
		if(listaReg.lista[i]->leido==0){
			buscar(gestor.listaCorreos, gestor.listaUsuarios.lista[gestor.activo]->listaRecibidos.lista[i]->identificador, x);
			correos.listaCorreos[correos.cont] = gestor.listaCorreos.listaCorreos[x];
			correos.cont++;
		}
	}
	ordenar_AF(correos);
	for(int i=0;i<correos.cont;i++){
		cout << "*" << setw(2) << i+1 << " - " << setw(3) << obtenerCabecera(*(correos.listaCorreos[i])) << endl;
	}
}


