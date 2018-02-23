package Practica3;

import java.io.BufferedReader;
import java.io.IOException;

import Celulas.Casilla;
import Excepciones.PalabraIncorrecta;

public class MundoComplejo extends Mundo {
	
	int NUMERO_CELULAS_COMPLEJAS;
	
	public MundoComplejo(int filas, int columnas, int simples, int complejas){
		
		super();
		this.filas = filas;
		this.columnas = columnas;
		this.NUMERO_CELULAS_SIMPLES = simples;
		this.NUMERO_CELULAS_COMPLEJAS = complejas;
		this.reiniciarSuperficie();
	}
	
	public MundoComplejo(int filas, int columnas){
		
		super();
		this.filas = filas;
		this.columnas = columnas;
		this.NUMERO_CELULAS_SIMPLES = 0;
		this.NUMERO_CELULAS_COMPLEJAS = 0;
		this.reiniciarSuperficie();
	}
	
	public void reiniciarSuperficie(){ 
		
		int x, y;
		superficie = new Superficie(this.filas, this.columnas);
		
		for(int i = 0; i < NUMERO_CELULAS_SIMPLES; i++){
			
			x =  (int)(Math.random()*(filas));
			y =  (int)(Math.random()*(columnas));
			
			while(!superficie.insertCelulaSimple(x, y)){ // si no se ha podido crear la celula en la posicion aleatoria generada buscamos otra en la que si se pueda

				x =  (int)(Math.random()*(filas));
				y =  (int)(Math.random()*(columnas));	
			}
			puntos.add(puntos.size(), new Casilla(x, y, ""));
		}
		for(int i = 0; i < NUMERO_CELULAS_COMPLEJAS; i++){
			
			x =  (int)(Math.random()*(filas));
			y =  (int)(Math.random()*(columnas));
			
			while(!superficie.insertCelulaCompleja(x, y)){ // si no se ha podido crear la celula en la posicion aleatoria generada buscamos otra en la que si se pueda

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
			if(superficie.esComestible(puntos.get(z).getX(), puntos.get(z).getY()) && superficie.comprobarReproduccion(casilla.getTexto())){
				superficie.moverCelula(puntos.get(z).getX(), puntos.get(z).getY(), casilla.getX(), casilla.getY());
				superficie.insertCelulaSimple(puntos.get(z).getX(), puntos.get(z).getY());
				puntos.add(puntos.size(), new Casilla(puntos.get(z).getX(), puntos.get(z).getY(), ""));
				puntos.set(z, casilla);
			}
			else if(superficie.comprobarMuerte(puntos.get(z))){
				if(superficie.esComestible(casilla.getX(), casilla.getY())){
					int i;
					i = this.buscarPosicion(casilla.getX(), casilla.getY());
					puntos.remove(i);
					superficie.eliminarCelula(casilla.getX(), casilla.getY());
					if(i < z) z--;
					if(i < t) t--;
				}
				superficie.eliminarCelula(puntos.get(z).getX(), puntos.get(z).getY());
				puntos.remove(z);
				z--;
				t--;
			}
			else if(!superficie.esComestible(puntos.get(z).getX(), puntos.get(z).getY()) && superficie.comprobarComer(casilla.getTexto())){
				int i ;
				superficie.moverCelula(puntos.get(z).getX(), puntos.get(z).getY(),casilla.getX(), casilla.getY());
				i = this.buscarPosicion(casilla.getX(), casilla.getY());
				puntos.set(z, casilla);
				puntos.remove(i);
				if(i < z) z--;
				if(i < t) t--;
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
	 * Nos permite crear una celula compleja en una determinada posicion del tablero si es posible y la añadimos al arraylist	
	 * @param x Coordenada de la fila de la celula
	 * @param y Coordenada de la columna de la celula
	 * @return <code>true</code> Cuando conseguimos crear una celula 
	 *     	   <code>false</code> En otro caso
	 */	
	public boolean crearCelula(int x, int y, Controlador ctrl){ // SCANER INNNNN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		boolean ok = false;
		String operando;
		
		operando = ctrl.preguntaOpcion();
					
		if(Integer.parseInt(operando) == 1){
			if(superficie.insertCelulaCompleja(x, y)) ok = true;
		}			
		else if(Integer.parseInt(operando) == 2){
			if(superficie.insertCelulaSimple(x, y)) ok = true;
		}
		
		if(ok == true)
			puntos.add(puntos.size(), new Casilla(x, y, ""));

		return ok;
	}
	
	public  void cargar(BufferedReader b) throws IOException, PalabraIncorrecta{ 
		
		String infoCelula;
		String []cadenaInfo;
		
	    infoCelula = b.readLine();
	    
	    while(infoCelula != null) {
	
			 cadenaInfo= infoCelula.split(" ");
			 
			 if(superficie.comprobarPos(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1])) == null){
				 if(cadenaInfo[2].equalsIgnoreCase("simple")){
					 
					 superficie.insertCelulaSimple(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1]), Integer.parseInt(cadenaInfo[3]), Integer.parseInt(cadenaInfo[4]));
					 puntos.add(puntos.size(), new Casilla(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1]), ""));
				 }
				 else if(cadenaInfo[2].equalsIgnoreCase("compleja")){
					 
					 superficie.insertCelulaCompleja(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1]), Integer.parseInt(cadenaInfo[3]));
					 puntos.add(puntos.size(), new Casilla(Integer.parseInt(cadenaInfo[0]), Integer.parseInt(cadenaInfo[1]), ""));
				 }
				 else{
					 throw new PalabraIncorrecta("El archivo tiene un formato incorrecto");
				 }
			 }
			 infoCelula = b.readLine();
	     }
	}
	
	public String guardar(){
		
		String texto = "";
		
		texto = texto + "complejo" + "\r\n" + this.filas + "\r\n" + this.columnas + "\r\n";
		for(int i= 0; i < puntos.size(); i++){
			
			if(superficie.esComestible(puntos.get(i).getX(), puntos.get(i).getY())){
				
				texto = texto + puntos.get(i).getX() + " " + puntos.get(i).getY() + " simple" + 
				superficie.getInfo(puntos.get(i).getX(), puntos.get(i).getY()) + "\r\n" ; 
			}		
			else{
				
				texto = texto + puntos.get(i).getX() + " " + puntos.get(i).getY() + " compleja" + 
				superficie.getInfo(puntos.get(i).getX(), puntos.get(i).getY()) + "\r\n" ; 
			}
		}
		return texto;
	}
			
}