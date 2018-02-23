package es.ucm.fdi.tp.Practica5;

import java.util.List;

import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.GameError;
import es.ucm.fdi.tp.basecode.bgame.model.GameMove;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNMove;

/**
 * Clase para representar un movimiento del juego Ataxx.
 * 
 */
public class AtaxxMove  extends GameMove {

	/**
	 * Fila en la que se coloca la ficha devuelta por
	 * {@link GameMove#getPiece()}.
	 */
	protected int row;
	
	/**
	 * Columna en la que se coloca la ficha devuelta por
	 * {@link GameMove#getPiece()}.
	 */
	protected int col;
	
	/**
	 * Fila en la que se colocara la ficha al moverse
	 */
	protected int destRow;
	
	/**
	 * Columna en la que se colocara la ficha al moverse
	 */
	protected int destCol;
	
	/**
	 * Se debe usar este constructor para obtener objetos de
	 * {@link AtaxxMove} para generar movimientos usando
	 * el metodo {@link #createConsolePlayer()}
	 * 
	 */
	public AtaxxMove() {
	}
	
	/**
	 * Construye un movimiento para colocar la ficha ubicada en la posicion ({@code row},{@code col}) en
	 * la posicion ({@code destRow},{@code destCol}).
	 * 
	 * @param row
	 *            Numero de fila.
	 * @param col
	 *            Numero de columna.
	 * @param destRow
	 *            Numero de fila destino.
	 * @param destCol
	 *            Numero de columna destino.
	 * @param p
	 *            Ficha a colocar en ({@code destRow},{@code destCol}).
	 */
	public AtaxxMove(int row, int col, int destRow, int destCol, Piece p) {
		super(p);
		this.row = row;
		this.col = col;
		this.destRow = destRow;
		this.destCol = destCol;
	}
	
	public void execute(Board board, List<Piece> pieces) {
		
		boolean encontrado = false;
		int i =0;
		
		if (getPiece().equals(board.getPosition(row, col))){
			
			if(Math.abs(destRow - row) <= 2 && Math.abs(destCol - col) <= 2)
				encontrado = true;
			
			if (encontrado && (board.getPosition(destRow, destCol)== null)) { // se mueve
				board.setPosition(destRow, destCol, getPiece());
				if(Math.abs(destRow - row) <= 1 && Math.abs(destCol - col) <= 1){ // distancia de 1 
					board.setPieceCount(getPiece(), board.getPieceCount(getPiece()) + 1);
				}
				else{ // distancia 2
					board.setPosition(row, col, null);
					//board.setPieceCount(getPiece(), board.getPieceCount(getPiece()) -1);
				}
				infectarR(board);
			} else {
				throw new GameError("Imposible to move (" + row + ", " + col + ") to (" + destRow + ", " + destCol + ")");
			}
		}
		else
			throw new GameError("position (" + row + "," + col + ") is not yours!");
	}

	/**
	 * Se puede construir un movimiento desde un string de la forma
	 * "row SPACE col SPACE destRow SPACE destCol" donde row, destRow y col, destCol son enteros que representan una casilla.
	 */
	@Override
	public GameMove fromString(Piece p, String str) {
		String[] words = str.split(" ");
		if (words.length != 4) {
			return null;
		}
		
		try {
			int row, col, destRow, destCol;
			row = Integer.parseInt(words[0]);
			col = Integer.parseInt(words[1]);
			destRow = Integer.parseInt(words[2]);
			destCol = Integer.parseInt(words[3]);
			return createMove(row, col, destRow, destCol, p);
		} catch (NumberFormatException e) {
			return null;
		}
	}
	
	/**
	 * Crea un nuevo movimiento con la misma ficha utilizada en el movimiento
	 * actual. Llamado desde {@link #fromString(Piece, String)}; se separa este
	 * metodo del anterior para permitir utilizar esta clase para otros juegos
	 * similares sobrescribiendo este metodo.
	 * 
	 * @param row
	 *            Fila del nuevo movimiento.
	 * 
	 * @param col
	 *            Columna del nuevo movimiento.
	 * @param destRow
	 *            Fila de destino del nuevo movimiento.
	 * @param destCol
	 *            Columna de destino del nuevo movimiento.
	 */
	protected GameMove createMove(int row, int col, int destRow, int destCol, Piece p) {
		return new AtaxxMove(row, col, destRow, destCol, p);
	}
	
	@Override
	public String help() {
		return "'row column', to place choose a piece and you can moved this to one or two position in any direction.";
	}
	
	public String toString() {
		if (getPiece() == null) {
			return help();
		} else {
			return "Moved the piece '" + getPiece() + "from"+ "(" + row + "," + col + ")" + "' to (" + destRow + "," + destCol + ")";
		}
	}
	
	public void infectarR(Board board){
		
		Piece q = new Piece("*");
		
		for(int i=-1; i<2; i++){
			//Elegimos una de las tres columnas que componen y rodean a la ceula
			if(destRow+i >= 0 && destRow+i < board.getRows()){
				//Vemos si la columna existe o es un margen (no existe)
				
				for(int m=-1; m<2; m++){
					//Dentro de cada columna elegimos una de las 3 posiciones posibles, de arriba a abajo
					if(destCol+m >= 0 && destCol+m < board.getCols()){
						//Determinamos si existe o esta fuera de rango
					
						if(board.getPosition(destRow+i, destCol+m) != null &&
								board.getPosition(destRow+i, destCol+m).getId() != q.getId() && 
								getPiece().getId() != board.getPosition(destRow+i, destCol+m).getId()){
							board.setPieceCount(getPiece(), board.getPieceCount(getPiece()) + 1);
							board.setPieceCount(board.getPosition(destRow+i, destCol+m), board.getPieceCount(board.getPosition(destRow+i, destCol+m)) - 1);
							board.setPosition(destRow+i, destCol+m, getPiece());

						} //Fin if
					}//End IndexOutOfBound
				}//End for Rows
			}//End if IndexOutOfBound
		}//End for Cols
	}
}
