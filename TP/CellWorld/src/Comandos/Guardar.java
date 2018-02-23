package Comandos;

import java.io.IOException;
import Practica3.Controlador;

/**
 * Clase Guardar, la cual hereda de la clase Comando. Permite guardar la partida en el fichero de texto indicado
 * <code>nombreFichero</code> - nombre del fichero que vamos a guardar
 */
public class Guardar implements Comando{

	private String nombreFichero;
	
	public Guardar(){
		super();
	}
	
	/**
	 * Constructor utilizado en el momento en que reconocemos que "guardar" es el comando deseado por el usuario
	 * @param cadenaComando utilizado para distinguir el nombre del fichero en el que queremos guardar
	 */
	public Guardar(String[] cadenaComando){
		
		this.nombreFichero = cadenaComando[1];
	}

	 /** 
	 * Invoca al metodo guardar de controlador el cual intenta guardar la partida en el fichero de texto indicado
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador 
	 * @return String indicando si se ha podido guardar la partida
	 */
	public String ejecuta(Controlador controlador) {
		
		String texto = "El juego se ha guardado correctamente";
		
		try {
			controlador.guardar(this.nombreFichero);
		} catch (IOException e) {

			texto = "Error al guardar el archivo";
		}
		return texto;
	}
	

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi creamos el comando guardar 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return devolvemos el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		
		if(cadenaComando.length == 2 && cadenaComando[0].equalsIgnoreCase("GUARDAR")){
			com = new Guardar(cadenaComando);
		}
		return com;
	}


	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		
		return "8- GUARDAR NOMFICH.txt: carga partida del NOMFICH.txt expecificado";
	}
}