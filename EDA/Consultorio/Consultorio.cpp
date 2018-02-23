#include <iostream>
#include <string>

#include "HashMap.h"
#include "List.h"

using namespace std;

class Consulta {
	typedef string Medico;
	typedef string Paciente;

private:
	HashMap<Medico, List<Paciente> > _medicos;
	HashMap<Paciente, int > _numCitas;

public:

	//crear consultorio vacio
	Consulta() {
	}

	//alta_medico(m)
	void altaMedico(Medico medico) {
		if (!_medicos.contains(medico)) {
			List<Paciente> p;
			//_medicos[medico] = p;
			_medicos.insert(medico, p);
		}
	}

	//pedir_vez(p,m)
	void pedirVez(Medico medico, Paciente paciente) {
		if (_medicos.contains(medico)) {
			_medicos[medico].push_back(paciente);
			if (_numCitas.contains(paciente))
				_numCitas[paciente]++;
			else
				_numCitas[paciente] = 1;
		}
	}

	//atenderConsulta(medico)
	void atenderConsulta(Medico medico) {
		if (_medicos.contains(medico) && !_medicos[medico].empty()) {
			Paciente p = _medicos[medico].front();
			_numCitas[p]--;
			_medicos[medico].pop_front();
		}
	}

	//tienePacientes(medico)
	void tienePacientes(Medico medico) {
		if (_medicos.contains(medico)) {
			if (_medicos[medico].empty())
				cout << "false" << endl;
			else
				cout << "true" << endl;
		}
		else
			cout << "false" << endl;
	}

	//pedirConEnchufe(Paciente, medico);
	void pideConEnchufe(Medico medico, Paciente paciente) {
		if (_medicos.contains(medico)) {
			_medicos[medico].push_front(paciente);
			if (_numCitas.contains(paciente))
				_numCitas[paciente]++;
			else
				_numCitas[paciente] = 1;
		}
	}

	//siguientePaciente(medico)
	void siguientePaciente(Medico medico) {
		if (_medicos.contains(medico)) {
			if (!_medicos[medico].empty())
				cout << _medicos[medico].front() << endl;
			else
				cout << "NADIE" << endl;
		}
		else
			cout << "NADIE" << endl;
	}

	//numCitas(paciente);
	void numCitas(Paciente paciente) {
		if (_numCitas.contains(paciente))
			cout << _numCitas[paciente] << endl;
		else
			cout << "0" << endl;
	}
};


int main() {


	int cont, i = 0;
	string palabra, medico, paciente;
	cin >> cont;
	while (i < cont) {
		Consulta c;
		cout << "bloque #" << i + 1 << endl;
		cin >> palabra;
		while (palabra != "fin") {
			if (palabra == "nuevoMedico") {
				cin >> medico;
				c.altaMedico(medico);
			}
			else if (palabra == "pideConsulta") {
				cin >> paciente >> medico;
				c.pedirVez(medico, paciente);
			}
			else if (palabra == "pideConEnchufe") {
				cin >> paciente >> medico;
				c.pideConEnchufe(medico, paciente);
			}
			else if (palabra == "siguientePaciente") {
				cin >> medico;
				c.siguientePaciente(medico);
			}
			else if (palabra == "tienePacientes") {
				cin >> medico;
				c.tienePacientes(medico);
			}
			else if (palabra == "atiendeConsulta") {
				cin >> medico;
				c.atenderConsulta(medico);
			}
			else if (palabra == "numCitas") {
				cin >> paciente;
				c.numCitas(paciente);
			}
			cin >> palabra;
		}
		i++;
	}
	return 0;
}
