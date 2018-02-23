package Practica3;

import java.util.*;
import Comandos.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import Excepciones.*;

/**
 * Clase Mundo, la cual esta rellena de celulas
 * <code>mundo</code> -  representa el mundo, al cual controla
 * <code>in</code> - atributo de tipo Scanner para la entrada de datos
 * <code>cadenaComandos</code> - String que contiene el texto que escribe el usuario
 * <code>simulacionTerminada</code> - indica si la simulacion del programa ha llegado a su fin
 */
public class Controlador {
	
	private Mundo mundo;
	private Scanner in;
	String[] cadenaComando;
	boolean simulacionTerminada;
	
	/**
	 * Constructor de la clase controlador
	 * @param in Inicializa la variable Scanner de la clase
	 * @param simulacionTerminada inicializa el atributo simulacionTerminada a false
	 */
	public Controlador(Scanner in){
		
		this.in = in;
		this.simulacionTerminada = false;
	}
	
	/**
	 * Gestiona el desarrollo del programa, lo hacemos mediante un bucle while del que solo se sale con el comando "SALIR"
	 */
	public void realizaSimulacion(){ 
		
		String[] cadenaComando;
		String frase;
		
		this.mundo = new MundoSimple(3,3);
		System.out.print("Comando > ");
		frase = in.nextLine();
		cadenaComando= frase.split(" ");
		Comando comando = ParserComandos.parseaComandos(cadenaComando);
		if (comando!=null) System.out.println(comando.ejecuta(this));

		do{	
			
		System.out.print(mundo.mostrarMundo());
		System.out.print("Comando > ");
		frase = in.nextLine();
		cadenaComando= frase.split(" ");
		
		comando = ParserComandos.parseaComandos(cadenaComando);
		if (comando!=null) System.out.println(comando.ejecuta(this));
		} while (!this.simulacionTerminada);
	
	}
	
	/**
	 * Nos permite saber si la simulacion va a terminar 
	 * @return <code>true</code> Cuando va a terminar la simulacion
	 *     	   <code>false</code> En otro caso
	 */
	public boolean esSimulacionTerminada(){
		
		return this.simulacionTerminada ;
	}
	
	/**
	 * Modifica el valor de this.salir
	 */
	public void terminar(){
		this.simulacionTerminada = true;
	}
	
	
	public boolean crearCelulaCtr(int x, int y){
		boolean creada = false;
		try{
			creada = mundo.crearCelula(x, y, this);
		}catch(ArrayIndexOutOfBoundsException e){
			System.out.println("La posicion especificada no existe en la superficie");
			creada = false;
		}catch(NumberFormatException e){
			System.out.println("El formato no es el correcto");
			creada = false;
		}
		return creada;
	}
	
	public void vaciar(){
		mundo.limpiarSuperficie();
	}
	
	public String paso(){
		return mundo.recorrerSuperficie();
	}
	
	public void iniciar(){
		mundo.reiniciarSuperficie();
	}
	
	public boolean eliminarCelulaCtr(int x, int y){
	boolean ok = false;
	try{
		mundo.eliminarCelula(x, y);
	}catch(ArrayIndexOutOfBoundsException e){
		System.out.println("La posicion especificada no existe en la superficie");
		ok = false;
	}
		 return ok;
	}
	
	public int preguntarOp(){
		int op =0;
		
		System.out.println("De que tipo: Compleja (1) o Simple (2):");
		op = in.nextInt();
		
		return op;
	}
	
	public void cambiarMundo(String[] cadenaComando){ 
		try{
			if(cadenaComando[1].equalsIgnoreCase("COMPLEJO")) this.mundo = new MundoComplejo(Integer.parseInt(cadenaComando[2]), Integer.parseInt(cadenaComando[3]), Integer.parseInt(cadenaComando[4]), Integer.parseInt(cadenaComando[5]));
			else this.mundo = new MundoSimple(Integer.parseInt(cadenaComando[2]), Integer.parseInt(cadenaComando[3]), Integer.parseInt(cadenaComando[4]));
		}
		catch(ArrayIndexOutOfBoundsException b){
			System.out.println("Has introducido mal los comandos");
		}
		catch(NumberFormatException c){
			System.out.println("Parametros para crear el mundo mal introducidos");
		}
	}
	
	
	public void cargar(String nombreFichero)throws FileNotFoundException, IOException, PalabraIncorrecta{
		
		String cadena, nombreArchivo;
		int filas, columnas;
		String[] cadenaModo;
		
		//nombreArchivo = "C:/Users/Andres/Google Drive/Pacticas TP/Practica3_TP/src/" + nombreFichero;
		//nombreArchivo = "C:/Users/Guillermo/Desktop/Google Drive/Pacticas TP/Practica3_TP/src/" + nombreFichero;
		nombreArchivo = "C:/Users/Kentor/Google Drive/Pacticas TP/Practica3_TP/src/" + nombreFichero;
        FileReader f = new FileReader(nombreArchivo);
        BufferedReader b = new BufferedReader(f);
        
        cadena = b.readLine();
        filas = Integer.parseInt(b.readLine());
        columnas = Integer.parseInt(b.readLine());
        cadenaModo = cadena.split(" ");
        
        if(cadenaModo[0].equalsIgnoreCase("simple")){
        	this.mundo = new MundoSimple(filas, columnas);
        }
        else if(cadenaModo[0].equalsIgnoreCase("complejo")){
        	this.mundo = new MundoComplejo(filas, columnas);
        }
        else{
        	b.close();
        	throw new PalabraIncorrecta("Archivo con formato incorrecto");
        }
        mundo.cargar(b);
        
        b.close();
	}
	
	public void guardar(String nomFich) throws IOException {
       // String ruta = "C:/Users/Andres/Google Drive/Pacticas TP/Practica3_TP/src/" + nomFich;
        String ruta = "C:/Users/Guillermo/Desktop/Google Drive/Pacticas TP/Practica3_TP/src/" + nomFich;
        
        File archivo = new File(ruta);
        BufferedWriter bw;
        bw = new BufferedWriter(new FileWriter(archivo));
        bw.write(mundo.guardar());
        bw.close();
    }
	
	
	public String preguntaOpcion(){
		String op = "";
		
		System.out.println("De que tipo: Compleja (1) o Simple (2):");
		op = this.in.nextLine();
		
		return op;
	}
}
