#ifndef ListaCorreos_h
#define ListaCorreos_h

#include "Correo.h"
#include <fstream>

using namespace std;

const string CENT = "X";

typedef tCorreo *tCorreoPtr;

typedef struct {
	tCorreoPtr *listaCorreos;
	int cont;
	int max;
}tListaCorreos;

namespace listaCorreos {
	void inicializar (tListaCorreos & correos);
	bool cargar (tListaCorreos & correos, string dominio);
	void guardar (const tListaCorreos & correos, string dominio);
	bool insertar (tListaCorreos & correos, const tCorreo & correo);
	}

bool buscar (const tListaCorreos & correos, string id, int & pos);
void ordenar_AF (tListaCorreos & correos);
bool operator< (tCorreo correo1, tCorreo correo2);
string asuntoRe(string asunto);

#endif