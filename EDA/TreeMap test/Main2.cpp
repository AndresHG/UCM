#include <iostream>
#include <cstdlib>
#include <sstream>
#include "TreeMap.h"

using namespace std;


int main() {

    int n,preguntas;
    cin >> n;
	//string prueba [3];
	string s, salida = "";
	getline (cin,s);

    for (int i=0; i<n; i++) {

		bool buscando = true;
		TreeMap <string, int> tree;
		getline (cin,s);

		while(buscando){
			size_t pos = -1;
			pos = s.find(" ");

			if(pos == -1){
				buscando = false;
				tree.insert(s.substr(0, pos), 1);
				//prueba[j] = s.substr(0,pos);
			}
			else{
				 tree.insert(s.substr(0, pos), 1);
				//prueba[j] = s.substr(0,pos);
				 s.erase(0, pos+1);
			}
		}

		cin >> preguntas;
		getline (cin,s);

		for (int j=0; j<preguntas; j++) {

			bool encontrado = true, fin = false;
			getline (cin,s);
			int pos = -1;

			while(encontrado && !fin){
				pos = -1;
				pos = s.find(" ");

				if(pos == -1){
					fin = true;
					if(!tree.contains(s)){

						encontrado = false;  
					}
				}
				else if(!tree.contains(s.substr(0,pos))){
					encontrado = false; 
				}
				s.erase(0, pos+1);
			}
			if(encontrado){
				salida = salida + "SI" + "\n";
			}
			else{
				salida = salida + "NO" + "\n";
			}
		}

	}

	cout << salida;

	system("PAUSE");
    return 0;

}

/*int main ()
{
  std::string name;

  std::cout << "Please, enter your full name: ";
  std::getline (std::cin,name);
  std::cout << "Hello, " << name << "!\n";

  return 0;
}

*/