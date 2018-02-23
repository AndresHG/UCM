#ifndef Correo_h
#define Correo_h

#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;

typedef time_t tFecha;
const string CENT_CORREO = "X";

typedef struct {
	string emisor;
	string destinatario;
	string asunto;
	string correo;
	tFecha fecha;
	string identificador;
}tCorreo;

namespace correo {
	bool cargar (tCorreo & correo , ifstream & archivo);
	bool guardar (const tCorreo & correo, ofstream & archivo);
}

void correoNuevo(tCorreo & correo, string emisor);
void correoContestacion (const tCorreo & correOriginal, tCorreo & correo, string emisor);
string aCadena (const tCorreo & correo);
string obtenerCabecera (const tCorreo & correo);

string mostrarFecha (tFecha fecha);
string mostrarFecha_SH (tFecha fecha);

#endif