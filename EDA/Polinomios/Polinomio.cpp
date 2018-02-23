#include <iostream>
#include <assert.h>

using namespace std;

/*
typedef struct {
	int coeficiente;
	int grado[];
}tPolinomio;

tPolinomio operator+(tPolinomio poli1, tPolinomio poli2) {


}

tPolinomio operator*(tPolinomio poli1, tPolinomio poli2) {


}

*/
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

	Polinomio(int grado, int coef[]) {
		this->grado = grado;
		for (int i = 0; i < this->grado; i++)
			this->coef[i] = coef[i];
	}

	Polinomio & operator+(const Polinomio &p) {
		if(p.grado < grado)
		{
			for (int i = 0; i <= p.grado; i++)
				coef[i] += p.coef[i];
		}
	else{
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

		this->grado = grado* p.grado;
		if (grado == 0 && coef[0] == 0)
			return Polinomio();
		else if(p.grado == 0 && p.coef[0] == 0)
			return Polinomio();

		for (int i = 0; i < this->grado; i++) {
			for (int j = 0; j < p.grado; j++) {
				coef[i+j] += coef[i] * p.coef[j];
			}
		}
	}

	string toString() {

		string palabra = "";
		if (coef[grado] == 0)
			palabra += coef[grado];
		else if(coef[grado] == 1)
			palabra += coef[grado] + "*n";
		else
			palabra += coef[grado] + "*n^" + grado;

		for (int i = grado -1; i >= grado; i++) {

			palabra += " + ";
			if (coef[i] == 0) 
				palabra += " + " + coef[grado];
			else if (coef[i] == 1) 
				palabra += coef[grado] + "*n";
			else
				palabra += coef[grado] + "*n^" + grado;
		}
	}

};

