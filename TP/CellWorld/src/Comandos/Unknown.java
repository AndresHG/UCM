package Comandos;

import Practica3.Controlador;

/**
 * Clase Unknown, la cual hereda de la clase Comando. Gestiona el programa cuando se introduce un comando incorrecto
 */
public class  Unknown implements Comando {

	/**
	 * Constructor vacio de la clase Unknown 
	 */
	public Unknown(){
		
	}

	 /** 
	 * Metodo al que invocaremos cuando el comando introducido no se corresponda con ninguno de los establecidos
	 * y que mostrara un string advirtiendo que el comando introducido es incorrecto 
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String que indica que el comando introducido es incorrecto
	 */	
	public String ejecuta(Controlador controlador) {
		return "Comando incorrecto, revise los comandos posibles en AYUDA";
	}

	/**
	 * Devuelve siempre como comando esta clase 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return devolvemos como comando la clase 
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = this;
		return com;
	}

	/**
	 * Metodo que devuelve un string vacio puesto que no hay ayuda para los comandos incorrectos 
	 * @return devuelve un string vacio
	 */
	public String textoAyuda() {
		return "";
	}	
}
