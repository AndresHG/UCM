package es.ucm.fdi.tp.pr5.connectn;

import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNFactory;


@SuppressWarnings("serial")
public class ConnectNFactoryExt extends ConnectNFactory {

	public ConnectNFactoryExt(Integer dim) {
		super(dim);
	}

	public ConnectNFactoryExt() {
	}

	@Override
	public void createSwingView(final Observable<GameObserver> g, final Controller c, final Piece viewPiece,
			final Player random, final Player auto) {
		
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				new ConnectNSwingView(g, c, viewPiece, random, auto);
			}
			
		});	
	}
}
