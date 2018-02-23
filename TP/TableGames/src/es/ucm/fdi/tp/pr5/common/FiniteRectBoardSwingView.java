package es.ucm.fdi.tp.pr5.common;

import java.awt.Color;
import java.util.List;

import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.pr5.common.BoardComponent.Shapes;


@SuppressWarnings("serial")
public abstract class FiniteRectBoardSwingView extends SwingView {

	private BoardComponent boardComp;
	private boolean active;
	
	public FiniteRectBoardSwingView(Observable<GameObserver> g, Controller c, Piece localPiece, Player randomPlayer,
			Player autoPlayer){
		super(g, c, localPiece, randomPlayer, autoPlayer);
		
	}

	@Override
	protected void initBoardGui() {
		
		boardComp = new BoardComponent(getBoard()){
		
			protected void mousePressed(int fila, int columna, int hola){
				
				//handleMousePressed(fila, columna,hola);
			}
			
			protected void mouseReleased(int fila, int columna, int hola){
				
				//handleMouseReleased(fila, columna,hola);
			}
			
			protected void mouseClicked(int fila, int columna, int hola){
				if(active)
					handleMouseClick(fila, columna, 0, hola);
			}
			
			@Override
			protected Shapes getPieceShape(Piece p){
				return FiniteRectBoardSwingView.this.getPieceShape(p);
			}
			@Override
			protected Color getPieceColor(Piece p) {
				// TODO Auto-generated method stub
				return FiniteRectBoardSwingView.this.getPieceColor(p);
			}
			
		};
		
		setBoardArea(boardComp); // install the board in the view		
	}
	
	

	protected abstract void handleMouseClick(int row, int col, int clickCount, int mouseButton);
	
	protected void redrawBoard(){
		
	}
	
	protected Shapes getPieceShape(Piece p){
		List <Piece> pieces = getPieces();
		if ( pieces != null && pieces.contains(p) ){
			return Shapes.CIRCLE;
		} 
		else {
			return Shapes.RECTANGLE;
		}
	}
	
	//Terminarrrrrrrr
	protected Color getPieceColor(Piece p){
		return super.getPieceColor(p);
	}
	
	public void setActive(boolean active){
		this.active = active;
	}
	
	protected abstract void handleMousePressed(int row, int col, int mouseButton);
	protected abstract void handleMouseReleased(int row, int col, int mouseButton);
	
	protected abstract String textoAyuda();
	protected void addStatus(String msg){
		
	}
	
}
