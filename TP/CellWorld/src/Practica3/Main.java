package Practica3;
import java.util.Scanner;

/**
 * Clase Main, la cual inicia y gestiona el programa
 * 
 * @see Controlador
 * @author: Guillermo Rius Garcia
 * @author: Andres Herranz Gonzelez
 * @version: 48/01/2016
 */

public class Main {

	/**
	 * Metodo que crea el Controlador, el Mundo y el Scanner e inicia el programa
	 * @param args generico de los main
	 */
	public static void main(String[] args) {		
		
		Controlador ctrl;
		//Mundo mundo;
		Scanner in = new Scanner(System.in); // Necesario para introducir datos por consola  
		ctrl = new Controlador(in);
		ctrl.realizaSimulacion(); 
	}

}
