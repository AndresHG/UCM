package Comandos;

import Excepciones.ErrorDeInicializacion;
import Practica3.Controlador;

/**
 * Clase Jugar, la cual hereda de la clase Comando. Permite iniciar la partida en el modo de juego indicado por el usuario
 * @param cadenaComando utilizado para distinguir el modo de juego 
 */
public class Jugar implements Comando{
	
	private String[] cadenaComando;

	/**
	 * Constructor de la clase Jugar(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public Jugar(){
		super();
	}
	
	/**
	 * Constructor de la clase Jugar(Clase que hereda de la clase Comando) el cual inicializa el String cadenaComando
	 */
	public Jugar(String[] cadenaComando){
		this.cadenaComando =  cadenaComando;
	}

	
	 /** 
	 * Invoca al metodo cambiarMundo de la clase Controlador el cual inicializa el mundo que se corresponda con el comando introducido
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String vacio
	 */
	public String ejecuta(Controlador controlador) {

		controlador.cambiarMundo(cadenaComando);
		
		return " ";
	}


	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y distinguimos el modo de juego que el usuario desea 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return devolvemos el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando)throws NumberFormatException, ErrorDeInicializacion{
		Comando com = null;
		
		if(cadenaComando[0].equalsIgnoreCase("JUGAR") && (cadenaComando[1].equalsIgnoreCase("SIMPLE") ||
				cadenaComando[1].equalsIgnoreCase("COMPLEJO"))){
			
			com = new Jugar(cadenaComando);
			
			if(cadenaComando.length == 5 && (Integer.parseInt(cadenaComando[2]) * Integer.parseInt(cadenaComando[3])) 
					<= (Integer.parseInt(cadenaComando[4]))){
				throw new ErrorDeInicializacion("Superado el tamaño maximo de la superficie");
			}
			
			if (cadenaComando.length == 6 && (Integer.parseInt(cadenaComando[2]) * Integer.parseInt(cadenaComando[3])) 
					<= (Integer.parseInt(cadenaComando[4]) + Integer.parseInt(cadenaComando[5]))){
				throw new ErrorDeInicializacion("Superado el tamaño maximo de la superficie");
			}
		}	
		return com;
	}

	
	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		return "9- JUGAR (MODO) F C CS (CC en modo complejo): Inicia el mundo del modo escogido creando las celulas indicadas";
	}
	
	
}
