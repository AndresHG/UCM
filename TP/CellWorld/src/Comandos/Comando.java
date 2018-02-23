package Comandos;

import Excepciones.ErrorDeInicializacion;
import Practica3.Controlador;

/**
 * Clase abstracta de la cual heredan los distintos comandos
 */
public interface Comando {
	
	/**
	 * Constructor vacio de la clase Comando 
	 */
	/*public Comando(){
			
	}*/
	
	 /** 
	 * Para cada comando el metodo ejecuta gestionara lo que debe ocurrir en la ejecucion 
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String orientativo con lo ocurrido en cada comando
	 */
	public abstract String ejecuta(Controlador controlador);
	
	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase  
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 * @throws ErrorDeInicializacion 
	 * @throws NumberFormatException 
	 */
	public abstract Comando parsea(String[ ] cadenaComando) throws NumberFormatException, ErrorDeInicializacion;
	
	/**
	 * Contiene el string que mostraremos como ayuda de cada clase
	 * @return devuelve el string con la ayuda de cada clase
	 */
	public abstract String textoAyuda();
	
}
