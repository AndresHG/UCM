package Practica3;

import Comandos.*;
import Excepciones.ErrorDeInicializacion;

/**
 * Clase ParserComandos que se encarga de gestionar el parsea de los comandos
 * <code>mundo</code> - comandos Array de Comando que contiene todos los comandos existentes
 */
public class ParserComandos {
	
	private static Comando[] comandos = {new Paso(), new Ayuda(), new CrearCelula(), new EliminarCelula(),
			new Iniciar(), new Vaciar(), new Cargar(), new Guardar(), new Jugar(), new Salir(), new Unknown()};
	
	public ParserComandos(){
		
	}
	
	/**
	 * Se encanrga de determinar cual es el comando que correponde al texto introducido por el usuario
	 * @param cadenaComandos array de strings que contiene el comando introducido 
	 * @return comando introducido por el usuario
	 */
	static public Comando parseaComandos(String[] cadenaComandos){
		Comando comando = null;
		int x=0;
		try{
			comando = comandos[x].parsea(cadenaComandos);
			
			while(comando == null && x < comandos.length){
				x++;
				comando = comandos[x].parsea(cadenaComandos);
			}
		}catch(NumberFormatException e){
			comando = new Unknown();
		}catch(ErrorDeInicializacion b){
			System.out.println(b.getMessage());
		}
		
		return comando;
	}
	
	/**
	 * Se encarga de almacenar en un string la ayuda de las distintas clases
	 * @return String con todos los textos de ayuda
	 */
	static public String AyudaComandos(){
		
		String textoAyuda = "";
		for(int x=0; x < comandos.length -1; x++){
			textoAyuda = textoAyuda + comandos[x].textoAyuda() + "\n";
		}
		
		return textoAyuda;
	}
}
