/**
  @file Stack.h

  Implementación del TAD Pila utilizando un
  vector dinámico cuyo tamaño va creciendo si
  es necesario.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __STACK_H
#define __STACK_H

#include "Exceptions.h"

/**
 Implementación del TAD Pila utilizando vectores dinámicos.

 Las operaciones son:

 - EmptyStack: -> Stack. Generadora implementada en el
   constructor sin parámetros.
 - Push: Stack, Elem -> Stack. Generadora
 - pop: Stack - -> Stack. Modificadora parcial.
 - top: Stack - -> Elem. Observadora parcial.
 - empty: Stack -> Bool. Observadora.
 - size: Stack -> Entero. Observadora.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Stack {
public:

	/** Tamaño inicial del vector dinámico. */
	static const int TAM_INICIAL = 10;

	/** Constructor; operación EmptyStack */
	Stack() {
		inicia();
	}

	/** Destructor; elimina el vector. */
	~Stack() {
		libera();
	}

	/**
	 Apila un elemento. Operación generadora.

	 @param elem Elemento a apilar.
	*/
	void push(const T &elem) {
		_v[_numElems] = elem;
		_numElems++;
		if (_numElems == _tam)
			amplia();
	}
	
	/**
	 Desapila un elemento. Operación modificadora parcial,
	 que falla si la pila está vacía.

	 pop(Push(elem, p)) = p
	 error: pop(EmptyStack)
	*/
	void pop() {
		if (empty())
			throw EmptyStackException();
		--_numElems;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operación
	 observadora parcial, que falla si la pila está vacía.

	 top(Push(elem, p) = elem
	 error: top(EmptyStack)

	 @return Elemento en la cima de la pila.
	 */
	const T &top() const {
		if (empty())
			throw EmptyStackException();
		return _v[_numElems - 1];
	}

	/**
	 Devuelve true si la pila no tiene ningún elemento.

	 empty(EmptyStack) = true
	 empty(Push(elem, p)) = false

	 @return true si la pila no tiene ningún elemento.
	 */
	bool empty() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el número de elementos que hay en la
	 pila.
	 size(EmptyStack) = 0
	 size(Push(elem, p)) = 1 + size(p)

	 @return Número de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Stack(const Stack<T> &other) {
		copia(other);
	}

	/** Operador de asignación */
	Stack<T> &operator=(const Stack<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
	bool operator==(const Stack<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		for (unsigned int i = 0; i < _numElems; ++i)
			if (_v[i] != rhs._v[i])
				return false;
		return true;
	}

	bool operator!=(const Stack<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void inicia() {
		_v = new T[TAM_INICIAL];
		_tam = TAM_INICIAL;
		_numElems = 0;
	}

	void libera() {
		delete []_v;
		_v = NULL;
	}

	void copia(const Stack &other) {
		_tam = other._numElems + TAM_INICIAL;
		_numElems = other._numElems;
		_v = new T[_tam];
		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = other._v[i];
	}

	void amplia() {
		T *viejo = _v;
		_tam *= 2;
		_v = new T[_tam];

		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = viejo[i];

		delete []viejo;
	}

private:

	/** Puntero al array que contiene los datos. */
	T *_v;

	/** Tamaño del vector _v. */
	unsigned int _tam;

	/** Número de elementos reales guardados. */
	unsigned int _numElems;
};

#endif // __STACK_H
