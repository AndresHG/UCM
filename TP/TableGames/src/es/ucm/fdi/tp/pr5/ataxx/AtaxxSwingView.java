package es.ucm.fdi.tp.pr5.ataxx;

import java.awt.Color;

import es.ucm.fdi.tp.Practica5.AtaxxRandomPlayer;
import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.pr5.common.FiniteRectBoardSwingView;


@SuppressWarnings("serial")
public class AtaxxSwingView extends FiniteRectBoardSwingView {

	private AtaxxSwingPlayer player;

	public AtaxxSwingView(Observable<GameObserver> g, Controller c, Piece localPiece, Player randomPlayer,
			Player autoPlayer) {
		
		super(g, c, localPiece, randomPlayer, autoPlayer);
		player = new AtaxxSwingPlayer();
		
	}

	@Override
	protected void handleMouseClick(int row, int col, int clickCount, int mouseButton) {
	
		if(mouseButton == 3)
			player = new AtaxxSwingPlayer();
		else if(player.getInicio() == true){
			player.setIniMoveValue(row, col);
			addContentToStatusArea("Click on the destination position");
		}
		else{
			player.setMoveValue(row, col);
			decideMakeManualMove(player);
		}
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
		//player.setIniMoveValue(row, col);
	}

	@Override
	protected void handleMouseReleased(int row, int col, int mouseButton) {
		// TODO Auto-generated method stub
		//player.setMoveValue(row, col);
		//if(getTurn() == getLocalPiece())
		//	decideMakeManualMove(player);
		
	}
	
	protected void decideMakeRandomMove(Piece turn){
		decideMakeManualMove(new AtaxxRandomPlayer());
	}
	
	protected String textoAyuda(){
		return "Click on an origin piece";
	}

}
