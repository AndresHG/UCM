package Comandos;

import Practica3.Controlador;

/**
 * Clase Paso, la cual hereda de la clase Comando. Realiza un paso cuando 
 * se pide a traves del comando correspondiente
 */
public class Paso implements Comando {
	
	/**
	 * Constructor de la clase Paso(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public Paso(){
		
		super();
	}

	 /** 
	 * Invoca al metodo recorrerSuperficie de la clase Mundo el cual se encarga de comprobar 
	 * todas las opciones en funcion de la posicion de destino para cada celula
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String con lo sucedido en el paso 
	 */
	public String ejecuta(Controlador controlador) {
		return controlador.paso();
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi realizamos un paso 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		if(cadenaComando.length == 1 && cadenaComando[0].equalsIgnoreCase("PASO")){
			com = new Paso();
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		return "1- PASO: realiza un paso en la simulacion";
	}

}
