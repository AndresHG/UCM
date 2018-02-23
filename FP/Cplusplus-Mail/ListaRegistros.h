#ifndef ListaRegistros_h
#define ListaRegistros_h
#include <string>
#include <fstream>

using namespace std;

typedef struct {
	string identificador;
	bool leido;
}tRegistroCorreo;
typedef tRegistroCorreo *tRegCorreoPtr;

typedef struct {
	tRegCorreoPtr *lista;
	int cont;
	int max;
}tListaRegistros;

namespace listaRegistros {
	void cargar (tListaRegistros &listaReg, ifstream & archivo);
	void guardar (const tListaRegistros & listaReg, ofstream & archivo);
	int buscar (const tListaRegistros & listaReg, string id);
	bool insertar (tListaRegistros & listaReg, tRegistroCorreo & registro);
	void inicializar (tListaRegistros & listaReg);

}

bool borrar (tListaRegistros & listaReg, string id);
bool correoLeido (tListaRegistros & listaReg, string id);
bool listaLleno(const tListaRegistros & listaC);

//Auxiliar
void ordenaXFecha (tListaRegistros & listaReg);
#endif