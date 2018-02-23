#include <iostream>
#include <cstdlib>
#include <sstream>

#include "Arbin.h"

using namespace std;

// lee a un arbol un texto que cumple la gramatica 
// ARBOL ::= ("VBOX"|"HBOX") ARBOL{0,2} END | RECT
// RECT  ::= INT{1,4} "x" INT{1,4}
// INT   ::= "0"|..."9"
Arbin<string> procesa(string actual) {
    Arbin<string> iz, dr;
    string siguiente;   
    if (actual[0] > '9') { // VBOX o HBOX
        while (cin >> siguiente) {
            if (siguiente == "END") {
                break;
            }                       
            if (iz.esVacio()) {            
                iz = procesa(siguiente);
            } else if (dr.esVacio()) {
                dr = procesa(siguiente);
            } else {
                cerr << "ERROR : tercer hijo " + siguiente << endl;
            }
        }
    }
    return Arbin<string>(iz, actual, dr);
}

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        string s;
        cin >> s;
        Arbin<string> a = procesa(s);
        // 
        // y aqui usas recursion sobre 'a' para 
        // calcular su ancho y alto finales, y los muestras
        //
    }
    return 0;
}
