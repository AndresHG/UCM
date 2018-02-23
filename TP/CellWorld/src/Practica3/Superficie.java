package Practica3;

import Celulas.*;

/**
 * Clase superficie, la cual esta rellena de celulas
 * 
 * <code>Celula[][]</code> -  representa la superficie bidimensional que contiene las celulas
 * <code>filas</code> - representa la altura de la superficie
 * <code>columnas</code> - representa la anchura de la superficie
 */
public class Superficie {

	private Celula[][] superficie;
	private int filas;
	private int columnas;
	
	/**
	 * Constructor que inicializa la superficie
	 * @param nf valor de el numero de filas que tendra la superficie
	 * @param nc valor de el número de columnas que tendra la superficie
	 */
	public Superficie(int nf, int nc){ 
		
		filas = nf; 
		columnas = nc;
		superficie = new Celula[filas][columnas];
		
		nuevaSuperficie();
	}
	
	/**
	 * Inicializa todas las posiciones de la superficie a null
	 */
	public void nuevaSuperficie(){ 
		
		for(int i = 0; i < this.filas; i++){
			for(int j = 0; j < this.columnas; j++){
			
				superficie[i][j] = null;
			}
		}
	}
	
	/**
	 * Invoca al metodo abstracto ejecutaMovimiento de la clase celula
	 * @param f valor de la variable f, para indicar la fila de la celula
	 * @param c valor de la variable c, para indicar la columna de la celula
	 * @return Devuelve la casilla a la que se movera la celula 
	 */
	public Casilla ejecutaMovimiento(int f, int c){
		
		return this.superficie[f][c].ejecutaMovimiento(f, c, this);
	}
	
	/**
	 * Devuelve lo que hay en la posicion de la superficie indicada
	 * @param x valor de la variable x, para indicar la posicion de la celula
	 * @param y valor de la variable y, para indicar la posicion de la celula
	 * @return Devuelve la celula o null si no existe
	 */
	public Celula comprobarPos(int x, int y){
		return this.superficie[x][y];
	}
	
	/**
	 * Modifica la posicion de la celula en la superficie
	 * @param x Coordenada x de la posicion de la celula que queremos mover
	 * @param y Coordenada y de la posicion de la celula que queremos mover
	 * @param libres Array de las casillas vacias a las que se va a poder mover la celula
	 * @return contador con el numero de posiciones libres que hay
	 */
	public int calcularMovimiento(int x, int y, Casilla[] libres){ // devuelve el array de pos libres 
		
		int cont=0;
		String texto = "";
		
		for(int i=-1; i<2; i++){
			//Elegimos una de las tres columnas que componen y rodean a la ceula
			if(y+i != -1 && y+i != this.columnas){
				//Vemos si la columna existe o es un margen (no existe)
				
				for(int m=-1; m<2; m++){
					//Dentro de cada columna elegimos una de las 3 posiciones posibles, de arriba a abajo
					if(x+m != -1 && x+m != this.filas){
						//Determinamos si existe o esta fuera de rango
					
						if(this.comprobarPos(x+m, y+i) == null){
							libres[cont] = new Casilla (x+m, y+i, texto);
							cont++;
						}
					}
				}
			}
		}
		return cont;
	}
	

	/**
	 * Modifica la posicion de la celula en la superficie
	 * @param x Coordenada x de la posicion antigua de la celula
	 * @param y Coordenada y de la posicion antigua de la celula
	 * @param nx Coordenada x de la posicion nueva de la celula
	 * @param ny Coordenada y de la posicion nueva de la celula
	 */
	public void moverCelula(int x, int y, int nx, int ny){ 
		superficie[nx][ny] = superficie[x][y];
		if(x != nx || y != ny)
			superficie[x][y] = null;
	}
	
	/**
	 * Crea una celula simple en la posición de la superficie indicada
	 * @param x valor de la variable x, para indicar la posicion de la celula
	 * @param y valor de la variable y, para indicar la posicion de la celula
	 */
	public boolean insertCelulaSimple(int x, int y) throws ArrayIndexOutOfBoundsException{ 
		boolean ok = false;
		
		if(superficie[x][y] == null){
			ok = true;
			superficie[x][y] = new CelulaSimple();
		}
		return ok;
	}
	
	public void insertCelulaSimple(int x, int y, int vida, int reproduccion)throws ArrayIndexOutOfBoundsException{ 
		superficie[x][y] = new CelulaSimple(vida, reproduccion);
	}
	
	/**
	 * Crea una celula compleja en la posición de la superficie indicada
	 * @param x valor de la variable x, para indicar la posicion de la celula
	 * @param y valor de la variable y, para indicar la posicion de la celula
	 */
	public boolean insertCelulaCompleja(int x, int y)throws ArrayIndexOutOfBoundsException{ 
		boolean ok = false;
		
		if(superficie[x][y] == null){
			ok = true;
			superficie[x][y] = new CelulaCompleja();
		}
		return ok;
	}
	
	public void insertCelulaCompleja(int x, int y, int comer) throws ArrayIndexOutOfBoundsException{ 
		superficie[x][y] = new CelulaCompleja(comer);
	}
	
	/**
	 * Elimina una celula poniendo la posicion de la superficie en la que se encontraba a null
	 * @param x valor de la coordenada x, para indicar la posicion de la celula
	 * @param y valor de la coordenada y, para indicar la posicion de la celula
	 * @return <code>true</code> Si se ha eliminado la celula 
	 *     	   <code>false</code> En caso contrario
	 */
	public boolean eliminarCelula (int x, int y){
		boolean ok = false;
		
		if(superficie[x][y] != null){
			superficie[x][y] = null;
			ok = true;
		}
		return ok;
	}
	
	/**
	 * Devuelve el valor de el atributo de clase, filas
	 * @return Valor de this.filas
	 */
	public int getFilas(){
		return this.filas;
	}
	
	/**
	 * Devuelve el valor de el atributo de clase, columnas
	 * @return Valor de this.columnas
	 */
	public int getColumnas(){
		return this.columnas;
	}
	
	/**
	 * Mostramos la superficie poniendo " -  " en las posiciones donde no hay celulas 
	 * y "*" para las c�lulas complejas, y "X" para las simples
	 * @return String que representa las celulas de la superficie
	 */
	public String mostrarSuperficie(){ 
		
		String nombre = "";
		
		for(int x=0; x< this.filas; x++){ // Recorremos la superficie en busca de celulas
			for(int y=0; y< this.columnas; y++){
				
				if(this.comprobarPos(x, y) == null){
					
					nombre = nombre + " - ";
				}
				else if (this.comprobarPos(x, y).esComestible()){
					
					nombre = nombre + " X ";
				}
				else{
					nombre = nombre + " * ";
				}
			}
			nombre = nombre + '\n';
		}
		nombre = nombre + '\n';
		
		return nombre;
	}
	
	/**
	 * Comprueba si una celula debe morir, y en caso afirmativo la pone a null
	 * @param casilla Representa las coordenadas de la celula que queremos comprobar
	 * @return <code>true</code> Si se ha eliminado la celula 
	 *     	   <code>false</code> En caso contrario
	 */
	public boolean comprobarMuerte(Casilla casilla){
		
		boolean ok = false;
		
		if(superficie[casilla.getX()][casilla.getY()].comprobarMuerte()){
			ok = true;
			this.eliminarCelula(casilla.getX(),casilla.getY());
		}
		return ok;
	}
	
	/**
	 * Comprueba si la celula indicada se debe reproducir
	 * @param texto Representa el el movimiento de la celula que queremos comprobar
	 * @return <code>true</code> Si se debe reproducir
	 *     	   <code>false</code> En caso contrario
	 */
	public boolean comprobarReproduccion(String texto){
		
		boolean ok = false;
		
		if(texto.indexOf("Nace") != -1){
			ok = true;
		}
		return ok;
	}
	
	/**
	 * Comprueba si la celula indicada ha comido
	 * @param texto Representa el el movimiento de la celula que queremos comprobar
	 * @return <code>true</code> Si ha comido
	 *     	   <code>false</code> En caso contrario
	 */
	public boolean comprobarComer(String texto){
		
		boolean ok = false;
		
		if(texto.indexOf("--COME--") != -1){
			ok = true;
		}
		return ok;
	}
	
	/**
	 * Comprueba si la celula indicada es comestible
	 * @param x valor de la coordenada x, para indicar la posicion de la celula
	 * @param y valor de la coordenada y, para indicar la posicion de la celula
	 * @return <code>true</code> Si la celula es comestible
	 *     	   <code>false</code> En caso contrario
	 */
	public boolean esComestible(int x, int y){
		
		return superficie[x][y].esComestible();
	}
	
	public  String getInfo(int x, int y){
			
		return superficie[x][y].getInfo();
	}
	
}
