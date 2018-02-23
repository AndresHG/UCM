package Excepciones;

/**
 * Clase de tipo Exception que se encarga de las excepciones por error de inicializacion
 */
public class ErrorDeInicializacion extends Exception{
	
	/**
	 * Constructor de la excepcion que se encarga de almacenar el mensaje
	 * @param msg mensaje con la informacion a cerca de el error cometido
	 */
	public ErrorDeInicializacion(String msg){
		super(msg);
	}
}