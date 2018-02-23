package es.ucm.fdi.tp.pr5.attt;

import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.basecode.attt.AdvancedTTTFactory;
import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNFactory;


@SuppressWarnings("serial")
public class AtttFactoryExt extends AdvancedTTTFactory {

	public AtttFactoryExt(Integer dim) {
		super();
	}

	public AtttFactoryExt() {
	}

	@Override
	public void createSwingView(final Observable<GameObserver> g, final Controller c, final Piece viewPiece,
			final Player random, final Player auto) {
		
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				new AtttSwingView(g, c, viewPiece, random, auto);
			}
			
		});	
	}
}
