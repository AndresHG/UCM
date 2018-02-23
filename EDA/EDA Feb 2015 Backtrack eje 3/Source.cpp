#include <iostream>
#include <string>


using namespace std;

const int n = 8;

struct prod{
	int p;
	int q;
	int c;
};

typedef prod productos[n];

void compra(const productos &prods, int k, int M, int Q, int &maxCal, bool marcas[n], prod act){

	if (k == n)
		return;

	for (int i = 0; i < n; i++){
		if (!marcas[i]){
			if (validO(prods[i], act, M, Q, maxCal)){
				marcas[i] = true;
				act.p += prods[i].p;
				act.q += prods[i].q;
				act.c += prods[i].c;

				if (act.q >= Q){
					if (maxCal > act.c)
						maxCal = act.c;
				}
					
				compra(prods, k + 1, M, Q, maxCal, marcas, act);
				marcas[i] = false;
				act.p -= prods[i].p;
				act.q -= prods[i].q;
				act.c -= prods[i].c;
			}
		}
	}
}

bool validO(prod p1, prod pact, int M, int Q, int cals){
	if (pact.p + p1.p <= M){
		if (cals == -1 || cals >= pact.c + p1.c)
			return true;
	}
	return false;
}


int main(){

	return 0;
}