package es.ucm.fdi.tp.pr5.connectn;

import java.awt.Color;

import es.ucm.fdi.tp.Practica5.AtaxxRandomPlayer;
import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNRandomPlayer;
import es.ucm.fdi.tp.pr5.common.FiniteRectBoardSwingView;


@SuppressWarnings("serial")
public class ConnectNSwingView extends FiniteRectBoardSwingView {

	private ConnectNSwingPlayer player;

	public ConnectNSwingView(Observable<GameObserver> g, Controller c, Piece localPiece, Player randomPlayer,
			Player autoPlayer) {
		
		super(g, c, localPiece, randomPlayer, autoPlayer);
		player = new ConnectNSwingPlayer();
		
	}

	@Override
	protected void handleMouseClick(int row, int col, int clickCount, int mouseButton) {
	 // do nothing if the board is not active	
		player.setMoveValue(row, col);
		decideMakeManualMove(player);
	}

	@Override
	protected void activateBoard() {
		// - declare the board active, so handleMouseClick accepts moves
		// - add corresponding message to the status messages indicating
		//   what to do for making a move, etc.
	}

	@Override
	protected void deActivateBoard() {
		// declare the board inactive, so handleMouseClick rejects moves
	}

	@Override
	protected void handleMousePressed(int row, int col, int mouseButton) {
		// TODO Auto-generated method stub
	}

	@Override
	protected void handleMouseReleased(int row, int col, int mouseButton) {
		// TODO Auto-generated method stub
		player.setMoveValue(row, col);
		decideMakeManualMove(player);
		
	}

	@Override
	protected void decideMakeRandomMove(Piece turn) {
		decideMakeManualMove(new ConnectNRandomPlayer());
	}
	
	protected String textoAyuda(){
		return "Click on an empty cell";
	}

}
