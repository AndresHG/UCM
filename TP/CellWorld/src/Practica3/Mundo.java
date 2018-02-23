package Practica3;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import Celulas.Casilla;
import Excepciones.PalabraIncorrecta;

/**
 * Clase Mundo, la cual esta rellena de celulas
 * 
 * <code>superficie</code> -  representa la superficie, a la cual controla
 * <code>filas</code> - representa la altura de la superficie como constante
 * <code>columnas</code> - representa la anchura de la superficie como constante
 * <code>puntos</code> - arraylist que contiene la posicion de las celulas de la superficie
 * <code>NUMERO_CELULAS_SIMPLES</code> - constante que representa numero de celulas simples iniciales
 * <code>NUMERO_CELULAS_COMPLEJAS</code> - constante que representa numero de celulas complejas iniciales
 */

public abstract class Mundo {

	protected int  NUMERO_CELULAS_SIMPLES;
	protected	Superficie superficie;
	protected int filas;
	protected int columnas;
	protected ArrayList<Casilla> puntos;
	
	/**
	 * Inicia el arraylist de puntos que contiene las casillas con las coordenadas de las celulas
	 * Inicializa la superficie
	 */
	public Mundo(){
		
		puntos = new ArrayList<Casilla>();
	}
	
	/**
	 * Crea una nueva superficie e introduce en posiciones aleatorias el numero de celulas marcado
	 */	
	public abstract void reiniciarSuperficie();
	
	
	public abstract boolean crearCelula(int x, int y, Controlador ctrl);

	public abstract void cargar(BufferedReader b) throws IOException, PalabraIncorrecta;
	
/**
 	* Se encarga de comprobar todas las opciones en funcion de la posicion de destino para cada celula
 * @return String con lo sucedido en el paso 
 */
	public abstract String recorrerSuperficie();

	
	/**
	 * Invoca al metodo de superficie, que vacia la misma y vacia el arraylist
	 */
	public void limpiarSuperficie(){   
		
		puntos.clear();
		this.superficie.nuevaSuperficie();
	}
	
	/**
	 * Nos permite eliminar una celula en una determinada posicion del tablero eliminandola a su vez del arraylist
	 * @param x Coordenada de la fila de la celula
	 * @param y Coordenada de la columna de la celula
	 * @return <code>true</code> Cuando eliminamos la celula 
	 *     	   <code>false</code> En otro caso
	 */
	public boolean eliminarCelula(int x, int y){
		boolean ok = false;
		if(superficie.comprobarPos(x, y) != null){
			puntos.remove(this.buscarPosicion(x, y));
			ok = superficie.eliminarCelula(x, y);
		}
		return ok;
	}
	
	/**
	 * Muestra la superficie y las celulas
	 * @return String con la superficie
	 */
	public abstract String mostrarMundo();
	public abstract String guardar();
	
	/**
	 * Nos permite buscar la posicion que ocupa la casilla de una celula en el arraylist
	 * @param x Coordenada de la fila de la celula
	 * @param y Coordenada de la columna de la celula
	 * @return Devuelve la posicion 
	 */
	public int buscarPosicion(int x, int y){
		int cont=0;
		boolean encontrado=false;
		while(!encontrado && cont < puntos.size()){
			
			if(x == puntos.get(cont).getX() && y == puntos.get(cont).getY())
				encontrado = true;
			else
				cont ++;
		}
		return cont;
	}
	
}
