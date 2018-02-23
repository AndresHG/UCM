package es.ucm.fdi.tp.pr5.ataxx;

import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.Practica5.AtaxxFactory;
import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.connectn.ConnectNFactory;


@SuppressWarnings("serial")
public class AtaxxFactoryExt extends AtaxxFactory {

	public AtaxxFactoryExt(Integer dim) {
		super(dim);
	}

	public AtaxxFactoryExt(Integer dim, Integer numObs) {
		super(dim, numObs);
	}
	
	public AtaxxFactoryExt() {
		
	}

	@Override
	public void createSwingView(final Observable<GameObserver> g, final Controller c, final Piece viewPiece,
			final Player random, final Player auto) {
		
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				new AtaxxSwingView(g, c, viewPiece, random, auto);
			}
			
		});	
	}
}
