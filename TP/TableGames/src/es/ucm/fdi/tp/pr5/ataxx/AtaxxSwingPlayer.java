package es.ucm.fdi.tp.pr5.ataxx;

import java.util.List;

import es.ucm.fdi.tp.Practica5.AtaxxMove;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.GameMove;
import es.ucm.fdi.tp.basecode.bgame.model.GameRules;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNMove;


@SuppressWarnings("serial")
public class AtaxxSwingPlayer extends Player {

	private int row;
	private int col;
	
	private int origRow;
	private int origCol;
	
	private boolean inicio;

	public AtaxxSwingPlayer() {
		inicio = true;
	}
	
	public boolean getInicio(){
		return this.inicio;
	}

	@Override
	public GameMove requestMove(Piece p, Board board, List<Piece> pieces, GameRules rules) {
		return createMove(row, col, p);
	}

	
	public void setMoveValue(int row, int col) {
		this.row = row;
		this.col = col;
		this.inicio = true;
		//this.destRow = a;
		//this.destCol = b;
	}
	
	public void setIniMoveValue(int row, int col) {
		this.origRow = row;
		this.origCol = col;
		this.inicio = false;
	}
	
	
	protected GameMove createMove(int row, int col, Piece p) {
		return new AtaxxMove(this.origRow, this.origCol, row, col, p);
	}
	
	//Revisarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr

}
