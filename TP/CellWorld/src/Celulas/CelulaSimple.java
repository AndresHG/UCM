package Celulas;
import Practica3.Superficie;

/**
 * Clase celulasimple, la cual gestiona los datos relativos a las celulas siemples
 * 
 * <code>MAX_PASOS_SIN_MOVER</code> -  constante que que nos indica cuantos pasos puede estar sin mover una celula antes de morir
 * <code>PASOS_REPRODUCCION</code> - constante que representa los pasos que tiene que dar la celula para reproducirse
 * <code>vida</code> - la vida de la celula
 * <code>reproducir</code> - la reproduccion de la celula
 * <code>esComestible</code> - atributo de tipo boolean sobre si la celula es comestible o no
 */
public class CelulaSimple implements Celula {

	protected final int MAX_PASOS_SIN_MOVER = 3; 
	protected final int PASOS_REPRODUCCION = 4;
	protected int vida; 
	protected int reproducir;
	protected boolean esComestible;
	
	/**
	 * Inicializan la vida y la reproduccion de la celula
	 */
	public CelulaSimple(){
		
		super();
		this.vida = 0;
		this.reproducir = 0;
		esComestible = true;	
	}
	
	/**
	 * Inicializan la vida y la reproduccion de la celula con los valores de los parámetros
	 */
	public CelulaSimple(int vida, int reproduccion){
		
		super();
		this.vida = vida;
		this.reproducir = reproduccion;
		esComestible = true;	
	}
	
	/**
	 * Nos permite saber que esta celula es comestible
	 * @return <code>true</code> Cuando la celula es comestible 
	 *     	   <code>false</code> En otro caso
	 */
	public boolean esComestible(){
		
		return this.esComestible;
	}
	
	/**
	 * Nos permite comprobar si la celula va a morir
	 * @return <code>true</code> Cuando la celula va a morir 
	 *     	   <code>false</code> En otro caso
	 */
	public boolean comprobarMuerte(){
	
		return this.vida == this.MAX_PASOS_SIN_MOVER;
	}
	
	/**
	 * Nos permite comprobar si la celula se va a reproducir
	 * @return <code>true</code> Cuando la celula se va a reproducir
	 *     	   <code>false</code> En otro caso
	 */
	public boolean comprobarReproduccion(){
		
		return this.reproducir == this.PASOS_REPRODUCCION;
	}
	
	/**
	 * Metodo que devulve la casilla a la que se mueve la celula simple que recibe e indica mediante el texto cual ha sido su evolucion
	 * @param f coordenada x de la celula que se va a mover
	 * @param c coordenada y de la celula que se va a mover
	 * @param superficie permite a celula acceder a superficie para hacer comprobaciones
	 * @return atributo x de la clase
	 */
	public Casilla ejecutaMovimiento(int f, int c, Superficie superficie) {
	
		int aleat;
		String texto = null;
		Casilla destino=null;
		Casilla[] libres = new Casilla[8]; // CAAMBIAR A ARRAYLISTTTTTT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int cont = superficie.calcularMovimiento(f, c, libres);
		
		if(superficie.calcularMovimiento(f, c, libres) != 0){
			aleat =  (int)(Math.random()*cont);
			this.reproducir++;
			if(this.comprobarReproduccion()){
				//Caso en el que se reproduce
				// superficie.insertCelulaSimple(f, c);
				texto = "La celula simple se ha movido de (" + f + ", " + c + ") a (" + libres[aleat].getX() + ", " +libres[aleat].getY()+")" + 
				" \n Nace una nueva celula en (" + f + ", " + c + ") cuyo padre ha sido(" + libres[aleat].getX() + ", " +libres[aleat].getY()+")" ; 
				destino = new Casilla(libres[aleat].getX(), libres[aleat].getY(), texto);
				this.reproducir = 0;
			}
			else{ // Solo se mueve
				texto = "La celula simple se ha movido de (" + f + ", " + c + ") a (" + libres[aleat].getX() + ", " + libres[aleat].getY() + ")";
				destino = new Casilla(libres[aleat].getX(), libres[aleat].getY(), texto);
			}
		}
		else{ // No se mueve 
			this.vida++;

			if(this.vida == this.MAX_PASOS_SIN_MOVER){ // Caso en el que se muere
				texto = "La celula simple HA MUERTO" ; 
				destino = new Casilla(-1,-1,texto);	
			}
			else{
				texto = "La celula simple no se ha movido" ; 
				destino = new Casilla(f,c,texto);
			}
		}
		return destino;
	}
	
	/**
	 * Contiene el string con informacion sobre los atributos vida y reproducir de la celula
	 * @return devuelve el string con la informacion sobre los atributos de la celula 
	 */
	public  String getInfo(){
		
		String texto = " " + this.vida + " " + this.reproducir;
			
		return texto;
	}	
}
