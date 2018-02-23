package Comandos;

import Practica3.Controlador;

/**
 * Clase EliminarCelula, la cual hereda de la clase Comando. Gestiona la eliminacion de celulas cuando 
 * se pide a traves del comando correspondiente
 * <code>fila</code> - representa la coordenada x de la superficie
 * <code>columna</code> - representa la coordenada y de la superficie
 */
public class EliminarCelula implements Comando {
	
	private int fila;
	private int columna;

	/**
	 * Constructor de la clase EliminarCelula(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public EliminarCelula(){
		super();
	}
	
	/**
	 * Constructor de la clase CrearCelulaSimple(Clase que hereda de la clase Comando) que se encarga de inicializar la fila 
	 * y la columna donde se eliminara la celula 
	 * @param fila representa la coordenada x de la superficie donde se eliminara la celula 
	 * @param columna representa la coordenada y de la superficie donde se eliminara la celula 
	 */
	public EliminarCelula(int fila, int columna){
		this.fila = fila;
		this.columna = columna;
	}

	 /** 
	 * Invoca al metodo eliminarCelula de mundo el cual intenta eliminar la celula de la posicion indicada
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String indicando si se ha podido eliminar la celula de la posicion indicada o no existia una celula en dicha posicion
	 */
	public String ejecuta(Controlador controlador) {
		String texto = "";
		
		if(controlador.eliminarCelulaCtr(this.fila, this.columna)){
			texto = "Eliminamos la celula de la posicion: (" + this.fila + ", " + this.columna + ")"; 
		}

		return texto;
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi intentamos eliminar la celula de la posicion indicada
	 * @param cadenaComando array de strings que contiene el comando introducido y la posicion donde se debe eliminar la celula
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando)throws NumberFormatException {
		Comando com = null;
		
		if(cadenaComando.length == 3 && cadenaComando[0].equalsIgnoreCase("ELIMINARCELULA")){
			com = new EliminarCelula(Integer.parseInt(cadenaComando[1]), Integer.parseInt(cadenaComando[2]));	
		}
		return com;
	}

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		// TODO Auto-generated method stub
		return "4- ELIMINARCELULA F C: elimina una celula compleja de la posicion (f,c) si es posible";
	}
	
}
