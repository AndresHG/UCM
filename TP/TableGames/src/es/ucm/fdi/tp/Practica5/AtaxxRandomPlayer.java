package es.ucm.fdi.tp.Practica5;

import java.util.ArrayList;
import java.util.List;

import es.ucm.fdi.tp.basecode.bgame.Utils;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.GameError;
import es.ucm.fdi.tp.basecode.bgame.model.GameMove;
import es.ucm.fdi.tp.basecode.bgame.model.GameRules;
import es.ucm.fdi.tp.basecode.bgame.model.Pair;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNMove;

/**
 * Un jugador aleatorio para Ataxx.
 *
 */
public class AtaxxRandomPlayer extends Player {

	@Override
	public GameMove requestMove(Piece p, Board board, List<Piece> pieces, GameRules rules) {
		
		if (board.isFull()) {
			throw new GameError("The board is full, cannot make a random move!!");
		}

		List<GameMove> moves = new ArrayList<GameMove>();
		
		moves = rules.validMoves(board, pieces, p);
		
		GameMove dev;
		if(moves.size() != 0){
			int rand = Utils.randomInt(moves.size());
			dev = moves.get(rand);
		}
		else
			dev = null;
		
	return dev;
	}

	/**
	 * Crea el movimiento concreto que sera devuelto por el jugador. Se separa
	 * este metodo de {@link #requestMove(Piece, Board, List, GameRules)} para
	 * permitir la reutilizacion de esta clase en otros juegos similares,
	 * sobrescribiendo este metodo.
	 * 
	 * @param row
	 *            row number.
	 * @param col
	 *            column number..
	 * @param p
	 *            Piece to place at ({@code row},{@code col}).
	 * @return
	 */
	protected GameMove createMove(int row, int col, Piece p) {
		return new ConnectNMove(row, col, p);
	}	
}
