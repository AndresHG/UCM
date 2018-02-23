package Comandos;

import Practica3.Controlador;

/**
 * Clase Salir, la cual hereda de la clase Comando. Gestiona la terminacion del programa cuando 
 * se pide a traves del comando correspondiente
 */
public class Salir implements Comando{

	/**
	 * Constructor de la clase Salir(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public Salir(){
		
		super();
	}
	
	 /** 
	 * Metodo al que invocaremos cuando queramos salir del programa y que mostrara un string despidiendose 
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String que indica que hemos terminado la ejecucion del programa 
	 */	
	public String ejecuta(Controlador controlador) {
		controlador.terminar();
		return " Hasta pronto!";
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		if(cadenaComando.length == 1 && cadenaComando[0].equalsIgnoreCase("SALIR")){
			com = new Salir();
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		
		return "0- SALIR: cierra la aplicacion";
	}

}
