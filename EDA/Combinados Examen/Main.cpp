#include <iostream>
#include "Deque.h"
#include "HashMap.h"

using namespace std;


/*
ConsultorioVacio: crea un nuevo consultorio vacío.
nuevoMedico: da de alta un nuevo médico en el consultorio.
pideConsulta: un paciente se pone a la espera de ser atendido por un médico.
pideConEnchufe: igual que la anterior, pero el paciente será atendido por delante del resto de pacientes.
tienePacientes: informa de si un médico tiene pacientes esperando.
siguientePaciente: consulta el paciente al que le toca el turno para ser atendido por un médico dado.
atiendeConsulta: elimina el siguiente paciente de un médico.
numCitas: indica el número de citas que un mismo paciente tiene en todo el consultorio.
*/

//void ConsultorioVacio(string nombre) crea un nuevo consultorio vacío.
class prod {

private:
	HashMap<string, Deque<string> > medicos;
	HashMap<string, int> pacientes;
	//HashMap<string, HashMap<string, int> > cosas;    //Prueba

public:
	void nuevoMedico(string nombre) {
		medicos[nombre];
	}//da de alta un nuevo médico en el consultorio.

	void pideConsulta(string paciente, string medico) {
		
		if (medicos.contains(medico)) {
			pacientes[paciente]++;
			medicos[medico].push_back(paciente);
			//HashMap<string, HashMap<string, int> >:: Iterator it = cosas.begin();
			//HashMap<string, int>::Iterator iter = it.value().begin();
		}
	}//un paciente se pone a la espera de ser atendido por un médico.


	void pideConEnchufe(string paciente, string medico) {
		if (medicos.contains(medico)) {
			pacientes[paciente]++;
			medicos[medico].push_front(paciente);
		}
	}//igual que la anterior, pero el paciente será atendido por delante del resto de pacientes.

	bool tienePacientes(string medico) {
		return medicos[medico].empty();
	}//informa de si un médico tiene pacientes esperando.

	string siguientePaciente(string medico) {
		if (!medicos.contains(medico) || medicos.at(medico).empty()) return " ";
		return medicos[medico].front();
	}//consulta el paciente al que le toca el turno para ser atendido por un médico dado.

	void atiendeConsulta(string medico) {
		if (medicos.contains(medico) && !medicos.at(medico).empty()) {
			pacientes[medicos[medico].front()]--;
			medicos[medico].pop_front();
		}
	}//elimina el siguiente paciente de un médico.

	int numCitas(string paciente) {
		return pacientes[paciente];
	}// indica el número de citas que un mismo paciente tiene en todo el consultorio.

};


int main(){

	string nomFunc;
	string nomArray[4];
	int cont = 0;
	int veces;
	cin >> veces;
	for (int i = 0; i < veces; i++){
		
		prod pdd;
		cout << "bloque #" << i+1 << "\n";
		getline(cin, nomFunc);
		while (nomFunc != "fin"){

			size_t pos = 0;
			while (pos != -1){
				pos = nomFunc.find(" ");
				nomArray[cont] = nomFunc.substr(0, pos);
				nomFunc.erase(0, pos + 1);
				cont++;
			}
			cont = 0;

			if (nomArray[0] == "nuevoMedico"){
				pdd.nuevoMedico(nomArray[1]);
			}

			else if (nomArray[0] == "pideConsulta"){
				pdd.pideConsulta(nomArray[1], nomArray[2]);
			}

			else if (nomArray[0] == "pideConEnchufe"){
				pdd.pideConEnchufe(nomArray[1], nomArray[2]);
			}

			else if (nomArray[0] == "tienePacientes"){
				if (!pdd.tienePacientes(nomArray[1]))
					cout << "true\n";
				else
					cout << "false\n";
			}

			else if (nomArray[0] == "siguientePaciente"){
				if (pdd.siguientePaciente(nomArray[1]) != " ")
					cout << pdd.siguientePaciente(nomArray[1]) << "\n";
				else
					cout << "NADIE\n";
			}

			else if (nomArray[0] == "atiendeConsulta"){
				pdd.atiendeConsulta(nomArray[1]);
			}

			else if (nomArray[0] == "numCitas"){
				cout << pdd.numCitas(nomArray[1]) << "\n";
			}

			getline(cin, nomFunc);

		}
	}

	return 0;
}