package Celulas;

import Practica3.Superficie;

/**
 * Clase celulaCompleja, la cual gestiona los datos relativos a las celulas complejas
 * 
 * <code>MAX_COMER</code> -  constante que que nos indica cuantas celulas simples puede comer la celula compleja antes de explotar
 * <code>explota</code> - atributo que contiene el numero de celulas simples que pueder la celula compleja antes de explotar
 * <code>esComestible</code> - atributo de tipo boolean sobre si la celula es comestible o no
 */
public class CelulaCompleja implements Celula{
	
	final int MAX_COMER = 3;
	int explota;
	protected boolean esComestible;
	
	/**
	 * Inicializa el explota de la celula y pone a false el es comestible indicando que la celula no es comestible
	 */
	public CelulaCompleja(){
		
		super();
		esComestible = false;	
		this.explota = 0;
	}
	
	/**
	 * Inicializa el explota de la celula con el valor que entra por parámetro y
	 * pone a false el es comestible indicando que la celula no es comestible
	 */
	public CelulaCompleja(int explota){
		
		super();
		esComestible = false;	
		this.explota = explota;
	}
	
	/**
	 * Nos permite comprobar que esta celula no es comestible
	 * @return <code>true</code> Cuando la celula es comestible 
	 *     	   <code>false</code> En otro caso
	 */
	public boolean esComestible(){
		
		return this.esComestible;
	}
	
	/**
	 * Nos permite comprobar si la celula va a morir
	 * @return <code>true</code> Cuando la celula debe morir 
	 *     	   <code>false</code> En otro caso
	 */
	public boolean comprobarMuerte(){
		
		return this.explota == this.MAX_COMER;
	}
	
	/**
	 * Metodo que devulve la casilla a la que se mueve la celula compleja que recibe e indica mediante el texto cual ha sido su evolucion
	 * @param f coordenada x de la celula que se va a mover
	 * @param c coordenada y de la celula que se va a mover
	 * @param superficie permite a celula acceder a superficie para hacer comprobaciones
	 * @return atributo x de la clase
	 */
	public Casilla ejecutaMovimiento(int f, int c, Superficie superficie) {
		
		int x,y;
		Casilla compleja = null;
		String texto;
		
			x =  (int)(Math.random()*superficie.getFilas());
			y = (int)(Math.random()*superficie.getColumnas());
	
			if(superficie.comprobarPos(x, y) != null && superficie.comprobarPos(x, y).esComestible()){
				this.explota++;
				
				if(this.explota == this.MAX_COMER){ //Caso en el que come y explota
					texto = "La celula compleja ha explotado"; 
					compleja = new Casilla(x, y,texto);
				}
				else{ //Caso en el que se mueve y come pero no explota
					texto = "La celula compleja se ha movido de (" + f + ", " + c + ") a (" + x + ", " + y + ") --COME--";  
					compleja = new Casilla(x, y, texto);
				}
			}
			else if(superficie.comprobarPos(x, y) == null){ //Caso en el que se mueve y no come
				texto = "La celula compleja se ha movido de  (" + f + ", " + c + ") a (" + x + ", " + y + ")--NO COME--";    
				compleja = new Casilla(x, y, texto);
			}
			else{ //Caso en el que se intenta mover a una posicion en la que hay una celula compleja y por tanto, no se mueve
				texto = "La celula compleja no se ha movido ";  
				compleja = new Casilla(-2, -2, texto);
			}
		
		return compleja;
	}
	
	/**
	 * Contiene el string con informacion sobre el atributo explota de la celula
	 * @return devuelve el string con la informacion sobre el atributo de la celula 
	 */
	public  String getInfo(){
		 
		String texto = " " + this.explota;		
		return texto;
	}
	
}

