package es.ucm.fdi.tp.Practica5;

import java.util.ArrayList;
import java.util.List;

import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.FiniteRectBoard;
import es.ucm.fdi.tp.basecode.bgame.model.GameError;
import es.ucm.fdi.tp.basecode.bgame.model.Game.State;
import es.ucm.fdi.tp.basecode.connectn.ConnectNMove;
import es.ucm.fdi.tp.basecode.bgame.model.GameMove;
import es.ucm.fdi.tp.basecode.bgame.model.GameRules;
import es.ucm.fdi.tp.basecode.bgame.model.Pair;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;

public class AtaxxRules implements GameRules{

	private int dim;
	private int numObstacles;
	
	public AtaxxRules(int dim, int numObstacles) {
		if (dim < 5 || (dim % 2 == 0) ) {
			throw new GameError("Dimension must be at least 5: " + dim + "and odd");
		} else {
			this.dim = dim;
			this.numObstacles = numObstacles;
		}
	}
	
	@Override
	public String gameDesc() {
		return "Ataxx " + dim + "x" + dim;
	}

	@Override
	public Board createBoard(List<Piece> pieces) {
		
		int x, y;
	    
		Board boardAtaxx = new FiniteRectBoard(dim, dim);
		
		if(pieces.size() > 3){			
			boardAtaxx.setPosition(0, (dim/2), pieces.get(3));
			boardAtaxx.setPosition(dim-1, (dim/2), pieces.get(3));
			boardAtaxx.setPieceCount(pieces.get(3), 2);
		}
		if(pieces.size() > 2){
			boardAtaxx.setPosition(dim/2, 0, pieces.get(2));
			boardAtaxx.setPosition(dim/2, (dim-1), pieces.get(2));
			boardAtaxx.setPieceCount(pieces.get(2), 2);
		}
		boardAtaxx.setPosition(0, 0, pieces.get(1));
		boardAtaxx.setPosition((dim-1), (dim-1), pieces.get(1));
		boardAtaxx.setPieceCount(pieces.get(1), 2);
		
		boardAtaxx.setPosition(0, (dim-1), pieces.get(0));
		boardAtaxx.setPosition((dim-1), 0, pieces.get(0));
		boardAtaxx.setPieceCount(pieces.get(0), 2);
		
		if(numObstacles < ((dim/2)*(dim/2))-1) {
		
			for(int i = 0; i < numObstacles; i++){
				
				x =  (int)(Math.random()*((dim/2)));
				y =  (int)(Math.random()*((dim/2)));
				
				while(boardAtaxx.getPosition(x, y) != null){
					x =  (int)(Math.random()*((dim/2)));
					y =  (int)(Math.random()*((dim/2)));
				}
				boardAtaxx.setPosition(x, y, new Piece("*"));
				boardAtaxx.setPosition(dim-1-x, y, new Piece("*"));
				boardAtaxx.setPosition(x, dim-1-y, new Piece("*"));
				boardAtaxx.setPosition(dim-1-x, dim-1-y, new Piece("*"));
			}	
		}
		else if(numObstacles < ((dim)*(dim))-1 -(pieces.size()*2)){
			
			for(int i = 0; i < numObstacles; i++){
				
				x =  (int)(Math.random()*((dim)));
				y =  (int)(Math.random()*((dim)));
				
				while(boardAtaxx.getPosition(x, y) != null){
					x =  (int)(Math.random()*((dim)));
					y =  (int)(Math.random()*((dim)));
				}
				boardAtaxx.setPosition(x, y, new Piece("*"));
			}	
			
			
		}
		
		return boardAtaxx;
	}

	@Override
	public Piece initialPlayer(Board board, List<Piece> playersPieces) {
		return playersPieces.get(0);
	}

	@Override
	public int minPlayers() {
		return 2;
	}

	@Override
	public int maxPlayers() {
		return 4;
	}

	@Override
	public Pair<State, Piece> updateState(Board board, List<Piece> pieces, Piece turn) {
		
		Pair<State, Piece> ganador = new Pair<State, Piece>(State.InPlay, null);
		List<Piece> playersPieces = new ArrayList<Piece>();
		boolean mov = false;
		
		for(int i=0;i<pieces.size();i++){
			
			if(validMoves(board, playersPieces, pieces.get(i)).size() != 0){
				mov = true;
			}
			
			if(board.getPieceCount(pieces.get(i)) == 0) 
				pieces.remove(i);
		}
		
		if(pieces.size() == 1){
			ganador = new Pair<State, Piece>(State.Won, pieces.get(0));
			return ganador;
		}
			
		if(board.isFull() || !mov){
			int max =0;
			for(int i=0;i<pieces.size();i++){
				int w = board.getPieceCount(pieces.get(i));
				if( w > max){
					max = w;
					ganador = new Pair<State, Piece>(State.Won, pieces.get(i));
				}
				else if (w == max){
					ganador = new Pair<State, Piece>(State.Draw, null);
				}
			}
			return ganador;
		}
		return ganador;
	}

	@Override
	public Piece nextPlayer(Board board, List<Piece> playersPieces, Piece lastPlayer) {
		List<Piece> pieces = playersPieces;
		int i = pieces.indexOf(lastPlayer);
		
		for(int j=1; j<(pieces.size()+1);j++){
			if(validMoves(board, pieces, pieces.get((i + j) % pieces.size())).size() != 0){
				return pieces.get((i + j) % pieces.size());
			}		
		}

		return pieces.get((i + 1) % pieces.size());
	}

	@Override
	public double evaluate(Board board, List<Piece> pieces, Piece turn, Piece p) {
		return 0;
	}

	@Override
	public List<GameMove> validMoves(Board board, List<Piece> playersPieces, Piece turn) {
		int rows = board.getRows();
		int cols = board.getCols();
		
		List<GameMove> moves = new ArrayList<GameMove>();
		
		for(int x=0; x < rows; x++){
			for(int y=0; y < rows; y++){	
				if(board.getPosition(x, y) == turn){
					moves.addAll(AtaxxRules.validMovesPiece(board, x, y, turn));
				}
			}
		}
		return moves;
	}
	
	/**
	 * Asigna el valor del atributo de clase @numObstacles
	 * @param numObstacles valor que se le asigna al atributo
	 */
	public void numObstacles(int numObstacles){
		
		 this.numObstacles = numObstacles;
	}
	
	/**
	 * Calcula los posibles movimientos de una ficha concreta
	 * @param board Tablero que contiene a las fichas
	 * @param x Coordeanada horizontal de la ficha	
	 * @param y Coordenada vertical de la ficha
	 * @param turn Tipo de pieza de la ficha elegida
	 * @return Lista con los posibles movimientos de la ficha
	 */
	public static List<GameMove> validMovesPiece(Board board, int x, int y, Piece turn) {
		List<GameMove> moves = new ArrayList<GameMove>();
		
		for(int i=-2; i<3; i++){
			//Elegimos una de las tres columnas que componen y rodean a la ceula
			if(x+i >= 0 && x+i < board.getCols()){
				//Vemos si la columna existe o es un margen (no existe)
				
				for(int m=-2; m<3; m++){
					//Dentro de cada columna elegimos una de las 3 posiciones posibles, de arriba a abajo
					if(y+m >= 0 && y+m < board.getRows()){
						//Determinamos si existe o esta fuera de rango
					
						if(board.getPosition(x+i, y+m) == null){
							moves.add(new AtaxxMove(x, y, x+i, y+m, turn));
						} //Fin if
					}//End IndexOutOfBound
				}//End for Rows
			}//End if IndexOutOfBound
		}//End for Cols
		return moves;
	}

}
