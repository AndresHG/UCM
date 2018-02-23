package Comandos;

import java.io.IOException;

import Excepciones.PalabraIncorrecta;
import Practica3.Controlador;

/**
 * Clase Cargar, la cual hereda de la clase Comando. Gestiona la carga de partidas
 * se pide a traves del comando correspondiente
 * <code>nombreFichero</code> - nombre del fichero que vamos a cargar
 */
public class Cargar implements Comando{

	private String nombreFichero;
	
	public Cargar(){
		super();
	}

	/**
	 * Constructor utilizado en el momento en que reconocemos que "cargar" es el comando deseado por el usuario
	 * @param cadenaComando utilizado para distinguir el nombre del fichero del que queremos cargar
	 */
	public Cargar(String[] cadenaComando){
		
		this.nombreFichero = cadenaComando[1];
	}

	 /** 
	 * Invoca al metodo cargar de controlador el cual intenta cargar la partida del fichero indicado
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador 
	 * @return String indicando si se ha podido cargar el archivo
	 */
	public String ejecuta(Controlador controlador) {
		
		String texto = "El archivo se ha cargado correctamente";
		
		try {
			controlador.cargar(this.nombreFichero);
		} catch (IOException e) {
			texto = ("No se ha podido encontrar el archivo");
		}catch (PalabraIncorrecta b){
			texto = b.getMessage();
		}
		return texto;
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi creamos el comando cargar 
	 * @param cadenaComando array de strings que contiene el comando introducido
	 * @return devolvemos el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando) {
		Comando com = null;
		
		if(cadenaComando.length == 2 && cadenaComando[0].equalsIgnoreCase("CARGAR")){
			com = new Cargar(cadenaComando);
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		
		return "7- CARGAR NOMFICH.txt: carga partida del NOMFICH.txt expecificado";
	}
}