#include <iostream>
#include <string>
#include "Arbin.h"
#include "HashMap.h"
#include "List.h"

using namespace std;

class barcoPesca{
	class Nada{};
	typedef string pescador, tipo;

private:
	int _max;
	int _actuales;
	HashMap<pescador, HashMap<tipo, int> > _barco;
	HashMap<tipo, int> _especies;

public:
	void nuevo(int kilos){
		_max = kilos;
		_actuales = 0;
	}
	void altaPescador(pescador pes){
		_barco[pes];
	}
	void nuevaCaptura(pescador pes, tipo espe, int kilos){
		if (_barco.contains(pes) && _actuales + kilos < _max){
			_barco[pes][espe] += kilos;
			_especies[espe] += kilos;
		}
	}
	List<pair<tipo, int>> capturasPescador(pescador pes){
		List<pair<tipo, int>> lista;
		HashMap<tipo, int>::ConstIterator it = _barco[pes].cbegin();
		for (it; it != _barco[pes].cend(); it++){
			lista.push_back(pair<tipo, int>(it.key(), it.value()));
		}
	}
	int kilosEspecie(tipo espe){
		return _especies[espe];
	}
	int kilosPescador(pescador pes){
		int suma=0;
		HashMap<tipo, int>::ConstIterator it = _barco[pes].cbegin();
		for (it; it != _barco[pes].cend(); it++){
			suma += it.value();
		}
		return suma;
	}
	int bodegarestante(){
		return _max - _actuales;
	}
};

int main(){
	
}