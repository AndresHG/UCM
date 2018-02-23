
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "Stack.h"
#include <cstdlib>
#include <sstream>

using namespace std;

class Polinomio {
private:
	int grado;
	int coef[20];

public:

	Polinomio() {
		this->grado = 0;
		for (int i = 0; i < 20; i++) {
			coef[i] = 0;
		}
	}

	Polinomio(int grado, int coeff[]) {
		this->grado = grado;
		for (int i = 0; i < 20; i++) {
			coef[i] = 0;
		}
		for (int i = 0; i <= this->grado; i++)
			this->coef[i] = coeff[i];
	}

	Polinomio & operator+(const Polinomio &p) {
		if (p.grado < grado)
		{
			for (int i = 0; i <= p.grado; i++)
				coef[i] += p.coef[i];
		}
		else {
			for (int i = 0; i <= p.grado; i++)
				coef[i] += p.coef[i];
			grado = p.grado;
		}
		return *this;
	}

	Polinomio & operator+(int num) {

		coef[0] += num;
		return *this;
	}

	Polinomio & operator*(const Polinomio &p) {

		int coefResult[20]{ 0 };
		this->grado = grado+p.grado;
		if (grado == 0 && coef[0] == 0)
			return Polinomio();
		else if (p.grado == 0 && p.coef[0] == 0)
			return Polinomio();

		for (int i = 0; i <= this->grado; i++) {
			for (int j = 0; j <= p.grado; j++) {
				coefResult[i + j] += coef[i] * p.coef[j];
			}
		}
		for (int i = 0; i <= this->grado; i++) {
			coef[i] = coefResult[i];
		}
	}

	string toString() {

		stringstream sgrado, scoef;
		scoef << coef[grado];
		sgrado << grado;
		string gradof = sgrado.str();
		string coeff = scoef.str();
		string palabra = "";

		if (grado == 0)
			palabra = coeff;
		else if (grado == 1 && coef[grado] != 1)
			palabra = coeff + "*n";
		else if (grado == 1 && coef[grado] == 1)
			palabra = "n";
		else if(coef[grado] != 1)
			palabra = coeff + "*n^" + gradof;
		else
			palabra = "n^" + gradof;
		for (int i = grado - 1; i >= 0; i--) {

			scoef.str("");
			sgrado.str("");
			sgrado << i;
			gradof = sgrado.str();
			scoef << coef[i];
			coeff = scoef.str();

			if (i == 0 && coef[i] != 0)
				palabra += " + " + coeff;
			else if (i == 1 && coef[i] != 1 && coef[i] != 0)
				palabra += " + " + coeff + "*n";
			else if (i == 1 && coef[i] == 1)
				palabra += " + n";
			else if (coef[i] != 1 && coef[i] != 0)
				palabra += " + " + coeff + "*n^" + gradof;
			if (coef[i] == 1)
				palabra += " + n^" + gradof;
		}

		return palabra;
	}

};

int main() {

	string nombre, n;
	Polinomio pol = Polinomio();
	Stack<string> instrucciones;
	Stack<Polinomio> polis;
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		pol = Polinomio();
		cin >> nombre; //BEGIN
		instrucciones.push(nombre);
		while (!instrucciones.empty()) {
			int j[20]{ 0 };
			cin >> nombre;
			if (nombre == "END") {
				while (!instrucciones.empty() && instrucciones.top() != "LOOP") {
					if (instrucciones.top() == "BEGIN")
						instrucciones.pop();
					else if (instrucciones.top() == "OP") {
						instrucciones.pop();
						pol+polis.top();
						polis.pop();
					}
				}
				if (!instrucciones.empty()) {
					instrucciones.pop();
					pol*polis.top();
					polis.pop();

					instrucciones.push("OP");
					polis.push(pol);
					pol = Polinomio();
				}
			}
			else {
				cin >> n;
				if (n == "n") {
					j[1] = 1;
					polis.push(Polinomio(1, j));
				}
				else {
					j[0] = atoi(n.c_str());
					polis.push(Polinomio(0, j));
				}
				instrucciones.push(nombre);
			}
		}
		cout << "Program #"  << i << "\n";
		cout << "Runtime = " << pol.toString() << "\n\n\n";
	}
	system("PAUSE");
	return 0;
}