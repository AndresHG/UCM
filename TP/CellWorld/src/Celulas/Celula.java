package Celulas;

import Practica3.Superficie;


/**
 * Clase abstracta de la cual heredan los distintos tipos de celulas
 */
public interface Celula {
	 
	
	/**
	 * Metodo que devulve la casilla a la que se mueve la celula que recibe
	 * @param f coordenada x de la celula que se va a mover
	 * @param c coordenada y de la celula que se va a mover
	 * @param superficie permite a celula acceder a superficie para hacer comprobaciones
	 * @return atributo x de la clase
	 */
	public abstract Casilla ejecutaMovimiento(int f, int c, Superficie superficie);	
	
	/**
	 * Nos permite comprobar si la celula es comestible
	 * @return <code>true</code> Cuando la celula es comestible 
	 *     	   <code>false</code> En otro caso
	 */
	public abstract boolean esComestible();
	
	/**
	 * Nos permite comprobar si la celula va a morir
	 * @return <code>true</code> Cuando la celula debe morir 
	 *     	   <code>false</code> En otro caso
	 */
	public abstract boolean comprobarMuerte();
	
	/**
	 * Contiene el string con informacion sobre los atributos de la celula 
	 * @return devuelve el string con la informacion sobre los atributos de la celula 
	 */
	public abstract String getInfo();
	
}
