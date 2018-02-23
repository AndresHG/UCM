package Practica3;

import java.io.BufferedReader;
import java.io.IOException;

import Celulas.Casilla;

public class MundoSimple extends Mundo {

	public MundoSimple(int filas, int columnas, int simples){
		super();
		this.filas = filas;
		this.columnas = columnas;
		this.NUMERO_CELULAS_SIMPLES = simples;
		this.reiniciarSuperficie();
	}
	
	public MundoSimple(int filas, int columnas){
		super();
		this.filas = filas;
		this.columnas = columnas;
		this.NUMERO_CELULAS_SIMPLES = 0;
		this.reiniciarSuperficie();
	}
	
	public void reiniciarSuperficie(){ 
		
		int x, y;
		superficie = new Superficie(this.filas, this.columnas);
		
		for(int i = 0; i < NUMERO_CELULAS_SIMPLES; i++){
			
			x =  (int)(Math.random()*(filas));
			y =  (int)(Math.random()*(columnas));
			
			while(!this.superficie.insertCelulaSimple(x, y)){ // si no se ha podido crear la celula en la posicion aleatoria generada buscamos otra en la que si se pueda

				x =  (int)(Math.random()*(filas));
				y =  (int)(Math.random()*(columnas));	
			}
			puntos.add(puntos.size(), new Casilla(x, y, ""));
		}
	}
	
	public String mostrarMundo(){
	
		return superficie.mostrarSuperficie();
	}
	
	/**
	 * Se encarga de comprobar todas las opciones en funcion de la posicion de destino para cada celula
	 * @return String con lo sucedido en el paso 
	 */
		public String recorrerSuperficie(){   
			
			String texto = "";		
			int t = puntos.size(), z=0;
			Casilla casilla;
			while(z < t){ // Realizamos la evolucion de cada celula
				
				casilla = superficie.ejecutaMovimiento(puntos.get(z).getX(), puntos.get(z).getY());
				texto = texto + casilla.getTexto() + "\n";
				
				if(superficie.comprobarReproduccion(casilla.getTexto())){
					superficie.moverCelula(puntos.get(z).getX(), puntos.get(z).getY(), casilla.getX(), casilla.getY());
					superficie.insertCelulaSimple(puntos.get(z).getX(), puntos.get(z).getY());
					puntos.add(puntos.size(), new Casilla(puntos.get(z).getX(), puntos.get(z).getY(), ""));
					puntos.set(z, casilla);
				}
				else if(superficie.comprobarMuerte(puntos.get(z))){
					superficie.eliminarCelula(puntos.get(z).getX(), puntos.get(z).getY());
					puntos.remove(z);
					z--;
					t--;
				}
				else if(casilla.getX() != -2){ //Solo se mueve
					superficie.moverCelula(puntos.get(z).getX(), puntos.get(z).getY(),casilla.getX(), casilla.getY());
					puntos.set(z, casilla);
				}
			
				z++;
			}
			return texto;
		}
	
	/**
	 * Nos permite crear una celula simple en una determinada posicion del tablero si es posible y la añadimos al arraylist	
	 * @param x Coordenada de la fila de la celula
	 * @param y Coordenada de la columna de la celula
	 * @return <code>true</code> Cuando conseguimos crear una celula 
	 *     	   <code>false</code> En otro caso
	 */	
	public boolean crearCelula(int x, int y, Controlador ctrl){ 
		
		boolean ok = false;
		if(superficie.comprobarPos(x, y) == null){ // es posible crearla si la posicion elegida es igual a null
				
			superficie.insertCelulaSimple(x, y);
			puntos.add(puntos.size(), new Casilla(x, y, ""));
			ok = true;
			}	
		return ok;
	}
	
	public  void cargar(BufferedReader b) throws IOException{
		
		//Exception a = new NumberFormatException();
		//a.
		String infoCelula;
		String []cadenaInfo;
		
		infoCelula = b.readLine();
	    
	    while(infoCelula != null) {
			 
	    	cadenaInfo= infoCelula.split(" ");
	    	
			 if(superficie.comprobarPos(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1])) == null){
				 
				 superficie.insertCelulaSimple(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1]), Integer.parseInt(cadenaInfo[3]), Integer.parseInt(cadenaInfo[4]));
				 puntos.add(puntos.size(), new Casilla(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1]), ""));
			 }
			 infoCelula = b.readLine();
	     }
	}
	
	public String guardar(){
		
		String texto = "";
		
		texto = texto + "simple" + "\r\n" + this.filas + "\r\n" + this.columnas + "\r\n";
		for(int i= 0; i < puntos.size(); i++){
			
			texto = texto + puntos.get(i).getX() + " " + puntos.get(i).getY() + " simple" + 
			superficie.getInfo(puntos.get(i).getX(), puntos.get(i).getY()) + "\r\n" ; 
		}
		
		return texto;
	}
	
}