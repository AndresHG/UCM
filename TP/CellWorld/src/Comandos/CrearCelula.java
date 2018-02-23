package Comandos;

import Practica3.Controlador;

/**
 * Clase CrearCelulaCompleja, la cual hereda de la clase Comando. Gestiona la creacion de celulas complejas cuando 
 * se pide a traves del comando correspondiente
 * <code>fila</code> - representa la coordenada x de la superficie
 * <code>columna</code> - representa la coordenada y de la superficie
 */
public class CrearCelula implements Comando{
	
	private int fila;
	private int columna;

	/**
	 * Constructor de la clase CrearCelulaCompleja(Clase que hereda de la clase Comando) y que llama al constructor de la clase padre
	 */
	public CrearCelula(){
		super();
	}
	
	/**
	 * Constructor de la clase CrearCelulaCompleja(Clase que hereda de la clase Comando) que se encarga de inicializar la fila 
	 * y la columna donde se creara la celula compleja
	 * @param fila representa la coordenada x de la superficie donde se creara la celula compleja
	 * @param columna representa la coordenada y de la superficie donde se creara la celula compleja
	 */
	public CrearCelula(int fila, int columna){
		this.fila = fila;
		this.columna = columna;
	}

	 /** 
	 * Invoca al metodo crearCelulaCompleja de mundo el cual intenta crear la celula compleja en la posicion indicada
	 * @param controlador el cual utilizamos para invocar a los métodos de controlador
	 * @return String indicando si se ha creado la celula o si no ha sido posible
	 */
	public String ejecuta(Controlador controlador) {
		String texto = "";
		
		if(controlador.crearCelulaCtr(this.fila, this.columna)){
			texto =  "Se ha creado una Celula: (" + this.fila + ", " + this.columna + ")"; 
		}
		return texto;
	}

	/**
	 * Comprueba que el comando introducido se corresponda con el de la clase y si es asi intentamos crear una celula compleja en la posicion indicada
	 * @param cadenaComando array de strings que contiene el comando introducido y la posicion donde se debe crear la celula
	 * @return el comando de la clase si se corresponde con el introducido, en caso contrario devolvemos null
	 */
	public Comando parsea(String[] cadenaComando)throws NumberFormatException {
		Comando com = null;
		
		if(cadenaComando.length == 3 && cadenaComando[0].equalsIgnoreCase("CREARCELULA")){
				com = new CrearCelula(Integer.parseInt(cadenaComando[1]), Integer.parseInt(cadenaComando[2]));
		}
		return com;
	}
	

	/**
	 * Contiene el string que mostraremos como ayuda de esta clase
	 * @return devuelve el string con la ayuda de esta clase
	 */
	public String textoAyuda() {
		return "3- CREARCELULA F C: crea una nueva celula  posicion (f,c) si es posible";
	}
	
	
}
