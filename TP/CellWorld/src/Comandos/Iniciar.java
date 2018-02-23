package Comandos;

import Practica3.Controlador;

/**
 * Clase Iniciar, la cual hereda de la clase Comando. Gestiona la Inicializacion de la superficie cuando 
 * se pide a traves del comando correspondiente
 */
public class Iniciar implements Comando {

	/**
	 * Constructor de la clase Iniciar(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public Iniciar(){
		
	}
	
	 /** 
	 * Invoca al metodo reiniciarSuperficie de la clase Mundo el cual crea una nueva superficie
	 * e introduce en posiciones aleatorias el numero de celulas marcado
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String que indica que la superficie ha sido iniciada
	 */
	public String ejecuta(Controlador controlador) {
		controlador.iniciar();
		return "Iniciamos el tablero";
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi iniciamos la superficie
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		if(cadenaComando.length == 1 && cadenaComando[0].equalsIgnoreCase("INICIAR")){
			com = new Iniciar();
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		return "5- INICIAR: inicia una nueva simulacion";
	}		

}
