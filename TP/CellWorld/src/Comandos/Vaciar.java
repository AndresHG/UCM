package Comandos;

import Practica3.Controlador;

/**
 * Clase Vaciar, la cual hereda de la clase Comando. Vacia la superficie cuando se pide a traves del comando correspondiente
 */
public class Vaciar implements Comando {

	/**
	 * Constructor de la clase Vaciar(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public Vaciar(){
		super();
	}

	 /** 
	 * Invoca al metodo limpiarSuperficie de la clase Mundo el cual vacia la superficie y el arraylist
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String que indica que la superficie ha sido vaciada
	 */
	public String ejecuta(Controlador controlador) {
		controlador.vaciar();
		return "Vaciamos la superficie";
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi vaciamos la superficie
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		if(cadenaComando.length == 1 && cadenaComando[0].equalsIgnoreCase("VACIAR")){
			com = new Vaciar();
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		return "6- VACIAR: vacia la superficie de celulas";
	}
	
}
