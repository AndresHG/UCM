package Excepciones;

/**
 * Clase de tipo Exception que se encarga de las excepciones por palabra incorrecta
 */
public class PalabraIncorrecta extends Exception{
	
	/**
	 * Constructor de la excepcion que se encarga de almacenar el mensaje
	 * @param msg mensaje con la informacion a cerca de el error cometido
	 */
	public PalabraIncorrecta(String msg){
		super(msg);
	}
}