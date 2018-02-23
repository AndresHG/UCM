package es.ucm.fdi.tp.pr5.common;

import java.awt.Color;
import java.util.List;

import javax.swing.JComponent;
import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.pr5.common.JBoard.Shapes;

public abstract class FiniteRectBoardSwingView extends SwingView {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public FiniteRectBoardSwingView(Observable<GameObserver> g, Controller c, Piece localPiece, Player randomPlayer,
			Player autoPlayer) {
		super(g, c, localPiece, randomPlayer, autoPlayer);
	}

	@Override
	protected void initBoardGui() {

		JComponent board = new JBoard(game) {
			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			@Override
			protected void mouseClicked(int row, int col, int clickCount, int mouseButton) {
				handleMouseClick(row, col, clickCount, mouseButton);
			}

			@Override
			protected Color getPieceColor(Piece p) {
				return FiniteRectBoardSwingView.this.getPieceColor(p);
			};
			
			@Override
			protected Shapes getPieceShape(Piece p) {
				return FiniteRectBoardSwingView.this.getPieceShape(p);
			}
		};

		setBoardArea(board);
	}

	protected Shapes getPieceShape(Piece p) {
		List<Piece> pieces = getPieces();
		
		if ( pieces != null && pieces.contains(p) ) {
			return Shapes.CIRCLE;
		} else {
			return Shapes.RECTANGLE;
		}
	}

	protected abstract void handleMouseClick(int row, int col, int clickCount, int mouseButton);

}
