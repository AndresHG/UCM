package Celulas;

/**
 * Clase Punto con dos atributos para indicar coordenadas de una celula y su evolucion
 * <code>x</code> - representa la coordenada de filas de una celula
 * <code>y</code> - representa la coordenada columnas de una celula
 * <code>texto</code> - representa la evolucion de la celula en este paso en forma de texto
 */
public class Casilla {

	private int x;
	private int y;
	private String texto;
	
	/**
	 * Constructor de Punto
	 * @param x coordenada para la representacion de la fila
	 * @param y coordenada para la representacion de la cloumna
	 * @param texto evolucion de la celula en este paso
	 */
	public Casilla(int x, int y, String texto){
		this.x=x;
		this.y=y;
		this.texto = texto;
	}
	
	/**
	 * Metodo que devulve la coordenada X de un punto
	 * @return atributo x de la clase
	 */
	public int getX(){
		return this.x;
	}

	/**
	 * Metodo que devulve la coordenada Y de un punto
	 * @return atributo y de la clase
	 */
	public int getY(){
		return this.y;
	}
	
	/**
	 * Metodo que devulve la evolucion de la celula
	 * @return atributo texto de la clase
	 */
	public String getTexto(){
		return this.texto;
	}

}


