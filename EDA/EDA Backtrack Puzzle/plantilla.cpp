#include <iostream>
#include <cstdlib>

#include "List.h"
#include "HashMap.h"

using namespace std;

class Nada {};

class Puzle {
    int c[9];  // contenido de las 9 casillas
    int z;     // indice del cero
    
    // funcion auxiliar para mover el cero de la casilla z a la casilla nextz
    // devuelve 'false' si no lo consigue
    // 0 1 2   - 2, 5, 8 no pueden moverse al este
    // 3 4 5     0, 3, 6 no pueden moverse al oeste
    // 6 7 8     nadie puede acabar > 8 ó < 0
    bool mueveZero(int nextz) {  
        if (nextz < 0 || nextz > 8
            || (z == 2 && nextz == 3) 
            || (z == 5 && nextz == 6) 
            || (z == 3 && nextz == 2) 
            || (z == 6 && nextz == 5) 
        ) {
            return false;
        }
        c[z] = c[nextz];
        c[nextz] = 0;
        z = nextz;
        return true;
    }

    
    //
    // funcion auxiliar para resolver el 8-puzle, llamada desde resuelve()
    // p - puzle actual
    // prof - profundidad maxima a la que buscar
    // vistos - 
    //
    static void resuelve(Puzle &p, int prof, HashMap<Puzle, Nada> &vistos,
                  List<char> &sol, List<char> &mejor) {
		if (!mejor.empty()) {
			return;
		}
		if (p.resuelto()){
			
				mejor = sol;
				return;	
		}
		if (prof == 0)
			return;

		for (int i = 0; i < 4; i++){
			char h = "enos"[i];
			if (p.mueve(h)) {
				if (!vistos.contains(p)) {
					vistos[p];
					sol.push_back(h);
					resuelve(p, prof - 1, vistos, sol, mejor);
					sol.pop_back();
					vistos.erase(p);
				}
				p.mueve("osen"[i]);
			}
		}
        // si resuelto
            // si solucion mas corta que la mejor
                // mejor = sol
            // y luego salgo, porque no tiene sentido seguir buscando
        
        // si prof == 0, salgo
        
        // para cada direccion
            // intento mover en esa direccion
                // si lo consigo
                    // y el resultado no esta en vistos
                        // meto p en vistos
                        // apilo la direccion de desplazamiento en sol
                        // me llamo recursivamente, con prof-1
                        // desapilo la ultima direccion de sol
                        // desmarco p en vistos
                // y deshago el movimiento
    }

public:

	bool deshacerMov(char dir){


		switch(dir) {
		case 'e': return mueveZero(z - 1);
		case 'n': return mueveZero(z + 3);
		case 'o': return mueveZero(z + 1);
		case 's': return mueveZero(z - 3);
		}
	}

	void muestra() const {
		for (int i = 0; i < 9; i++) {
			cout << c[i] << (i == 8 ? "" : " ");
		}
		cout << "\n";
	}

    // otras funciones aqui: carga, mueve, ...

	bool mueve(char dir){
		switch (dir) {
		case 'e': return mueveZero(z + 1);
		case 'n': return mueveZero(z - 3);
		case 'o': return mueveZero(z - 1);
		case 's': return mueveZero(z + 3);
		}
	}

	void carga(int vector[]){
		for (int i = 0; i < 9; i++)
			c[i] = vector[i];
		z = 0;
		while (c[z] != 0)
			z++;
	}

	bool resuelto() const{
		int i = 0;
		while (i < 8 && c[i] == i + 1){
			i++;
		}
		return i == 8 ? true : false;
	}

    // O((d*d) !) , aunque generalmente mucho mucho menos
    List<char> resuelve() const {
        List<char> mejor;
        if ( ! resuelto()) {
            List<char> sol;
            HashMap<Puzle, Nada> vistos;
            Puzle p = *this;
            for (int prof=4; mejor.empty(); prof ++) {
                Puzle::resuelve(p, prof, vistos, sol, mejor); 
            }
        }
        return mejor;
    }
    
    // necesario para que Puzle pueda ser clave de hashmap
    unsigned int hash() const {
        unsigned int r=0;
        for (int i=0; i<9; i++) r = r*10 + c[i];
        return r;
    }
    // necesario para que Puzle pueda ser clave de hashmap
    bool operator==(const Puzle &o) const {
        for (int i=0; i<9; i++) if (o.c[i] != c[i]) return false;
        return true;
    }
};

int main() {
    int n;
    int linea = 1;
    cin >> n;
    for (int i=0; i<n; i++) {
        cout << "bloque #" << (i+1) << '\n';
        Puzle p;
        string op, dir;
        while (cin >> op && op != "fin") {
            linea ++;
            if (op == "carga") {
                int leido[9];
                for (int j=0; j<9; j++) cin >> leido[j];
                // asume que esperas un array de 9 ints
                p.carga(leido);            
            } else if (op == "muestra") { 
                cout << linea << ": ";
                p.muestra();
            } else if (op == "resuelto") { 
                cout << linea << ": ";
                cout << (p.resuelto() ? "true\n" : "false\n");

            } else if (op == "mueve") { 
                cin >> dir; 
                cout << linea << ": ";
                cout << (p.mueve(dir[0]) ? "true\n" : "false\n");
            } else if (op == "resuelve") { 
                cout << linea << ": ";
                List<char> solucion = p.resuelve();
                for (List<char>::ConstIterator it=solucion.cbegin();
                     it != solucion.cend(); it++) {
                    cout << *it << " ";
                }
                cout << "\n";
            } else {
                cerr << "ERROR: ??OP " << op << '\n';
            }
        }
        linea ++;
    }
    return 0;
}