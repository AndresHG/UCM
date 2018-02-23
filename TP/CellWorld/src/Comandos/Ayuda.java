package Comandos;

import Practica3.Controlador;
import Practica3.ParserComandos;

/**
 * Clase Ayuda, la cual hereda de la clase Comando. Gestiona la ayuda cuando 
 * se pide a traves del comando correspondiente
 */
public class Ayuda implements Comando{

	/**
	 * Constructor de la clase Ayuda(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public Ayuda(){
		super();
	}

	 /** 
	 * Invoca al metodo ayudaComandos de la clase Parser Comandos el cual devuelve un string con todos los textos de ayuda
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String con todos los textos de ayuda
	 */
	public String ejecuta(Controlador controlador) {
		return ParserComandos.AyudaComandos();
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi iniciamos la ayuda 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return devolvemos el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		
		if(cadenaComando.length == 1 && cadenaComando[0].equalsIgnoreCase("AYUDA")){
			com = new Ayuda();
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		
		return "2- AYUDA: muestra esta ayuda";
	}
}
