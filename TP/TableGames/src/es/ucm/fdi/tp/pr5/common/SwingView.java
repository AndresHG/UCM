package es.ucm.fdi.tp.pr5.common;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;

import es.ucm.fdi.tp.Practica5.AtaxxRandomPlayer;
import es.ucm.fdi.tp.basecode.bgame.Utils;
import es.ucm.fdi.tp.basecode.bgame.control.Controller;
import es.ucm.fdi.tp.basecode.bgame.control.Player;
import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;
import es.ucm.fdi.tp.basecode.bgame.model.Game.State;
import es.ucm.fdi.tp.pr5.connectn.ConnectNSwingPlayer;
import es.ucm.fdi.tp.basecode.bgame.model.GameError;


@SuppressWarnings("serial")
public abstract class SwingView extends JFrame implements GameObserver {

	protected Controller ctrl;
	protected Observable<GameObserver> game;
	
	private Piece turn;
	private List<Piece> pieces;
	private Map<Piece, Color> pieceColors;
	private Piece localPiece;
	Iterator<Color> colorsIter;
	private boolean inPlay;
	protected String gameDesc;
	private JButton restartButt;
	private JButton quitButt;
	
	JButton randomButt;
	JButton aiButt;

	private Board board;

	private JPanel boardPanel;
	private JPanel toolBarPanel;
	private JPanel movesPanel;
	private JTextArea statusArea;
	private JComboBox<Piece> playerModesCB;
	private JComboBox<PlayerMode> modesCB;
	private JComboBox<Piece> playerColorsCB;
	private PlayerInfoTableModel playerInfoTable;
	
	class PlayerInfoTableModel extends DefaultTableModel {
		private String[] colNames = { "Player", "Mode", "#Pieces" };
		
		@Override
		public String getColumnName(int col) {
			return colNames[col];
		}
		// SOLUCIONAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		@Override
		public int getColumnCount() {
			return 3;
			//return colNames.length;
		}
		@Override
		public int getRowCount() {
			
			if(SwingView.this.pieces == null){
				return 0;
			}
			else{
				return SwingView.this.pieces.size();
			}
			//return SwingView.this.pieces == null ? 0 : SwingView.this.pieces.size();
		}
		@Override
		public Object getValueAt(int rowIndex, int columnIndex) {
			if (SwingView.this.pieces == null) {
				return null;
			}
			Piece p = SwingView.this.pieces.get(rowIndex);
			if (columnIndex == 0) {
				return p;
			} else if (columnIndex == 1) {
				return SwingView.this.playerTypes.get(p);
			} else {
				return SwingView.this.board.getPieceCount(p);
			}
		}
		public void refresh() {
			fireTableDataChanged();
		}
	};
	
	private Map<Piece, PlayerMode> playerTypes;
	private Player randomPlayer;
	private Player aiPlayer;
		
		enum PlayerMode {
			MANUAL("Manual"), RANDOM("Random"), AI("Intelegent");
			
			private String name;
			
			PlayerMode(String name) {
				this.name = name;
			}
			@Override
			public String toString() {
				return name;
			}
		}
	/**
	 * Permite saber el color de un jugador
	 * @param p Jugador o pieza del que queremos saber el color	
	 * @return Devuelve el color de la pieza
	 */
	protected Color getPieceColor(Piece p) {
		
		Color c = pieceColors.get(p);
		if (c == null) {
			c = colorsIter.next();
			pieceColors.put(p, c);
		}
		return c;
	}
	
	/**
	 * Metodo de acceso a la pieza que le toca
	 * @return Turno actual
	 */
	protected Piece getTurn() {
		return turn;
	}
	
	/**
	 * Metodo de acceso a la pieza local de la SwingView(solo en miltiview)
	 * @return Pieza local localPiece
	 */
	protected Piece getLocalPiece() {
		return localPiece;
	}

	/**
	 * Metodo de acceso a las piezas del juego
	 * @return Lista de piezas (jugadores)
	 */
	final protected List<Piece> getPieces() {
		return pieces;
	}
	
	/**
	 * Metodo de acceso al tablero de la SwingView
	 * @return Devuelve el board
	 */
	protected Board getBoard() {
		return board;
	}
	
	/**
	 * Permite modificar el boardPanel y agrgarle lo que le entra por parameros
	 * @param c componente an insertar en el boardPanel
	 */
	final protected void setBoardArea(JComponent c) {
		boardPanel.add(c, BorderLayout.CENTER);
	}
	
	/**
	 * Permite añadir al toolBarPanel el componente que le llega
	 * @param c componente a insertar en el toolBarPanel
	 */
	final protected void addToCtrlArea(JComponent c) {
		toolBarPanel.add(c);
	}

	/**
	 * Permite añadir un mensaje al statusArea
	 * @param msg mensaje a mostrar
	 */
	final protected void addContentToStatusArea(String msg) {
		statusArea.append("* " + msg + "\n");
	}

	protected void addStatus(String msg){
		addContentToStatusArea(msg);
	}
	
	protected abstract void initBoardGui();

	protected abstract void activateBoard();

	protected abstract void deActivateBoard();


	/**
	 * Constructor de la SwingView
	 * @param g contine el juego
	 * @param c permite a la swingView acceso al controlador
	 * @param localPiece le asigna a cada ventana Un jugador (solo en el modo multiview)
	 * @param randomPlayer inicializa un objeto de tipo randomPlayer
	 * @param aiPlayer inicializa un objeto de tipo aiPlayer
	 */
	public SwingView(Observable<GameObserver> g, Controller c, Piece localPiece, Player randomPlayer, Player aiPlayer) {

		this.ctrl = c;
		this.game = g;
		this.colorsIter = Utils.colorsGenerator();
		this.pieceColors = new HashMap<Piece, Color> ();
		this.playerTypes = new HashMap<Piece, PlayerMode> ();
		this.localPiece = localPiece ;
		this.randomPlayer = randomPlayer;
		this.aiPlayer = aiPlayer;
		this.inPlay = false;

		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				game.addObserver(SwingView.this);
			}
			
		});	
	}

	/**
	 * Llama al controlador para que ejecute un movimiento
	 * @param player contiene los datos del movimiento qu ese desea realizar 
	 */
	protected void decideMakeManualMove(Player player) {
		this.ctrl.makeMove(player);
	}
	
	
	/**
	 * Iniciliza la ventana
	 */
	private void initGUI() {
		
		String title = "Board Games: ";
		String titleLoop[] = gameDesc.split(" ");
		title += titleLoop[0];
		
		if(localPiece != null){
			title += " (" + localPiece.getId() + ")";
			this.setTitle(title);
		}
		else
			this.setTitle(title);
		
			JPanel mainPanel = new JPanel(new BorderLayout());
			mainPanel.setPreferredSize(new Dimension(750,500));
		
		this.setContentPane(mainPanel);

			 // board panel
				this.boardPanel = new JPanel(new BorderLayout());
			
			mainPanel.add(boardPanel, BorderLayout.CENTER);
			
		initBoardGui();

			 // tool bar panel
				toolBarPanel = new JPanel();
			 toolBarPanel.setLayout(new BoxLayout(toolBarPanel, BoxLayout.Y_AXIS));
			
			mainPanel.add(toolBarPanel, BorderLayout.LINE_END);
			
		initCtrlPanel();

		this.addWindowListener(new WindowListener() {

			@Override
			public void windowClosing(WindowEvent e) {
				quit();
			}

			@Override
			public void windowOpened(WindowEvent e) {
			}

			@Override
			public void windowIconified(WindowEvent e) {
			}

			@Override
			public void windowDeiconified(WindowEvent e) {
			}

			@Override
			public void windowDeactivated(WindowEvent e) {
			}

			@Override
			public void windowClosed(WindowEvent e) {
			}

			@Override
			public void windowActivated(WindowEvent e) {
			}
			
		});

		this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		this.pack();
		this.setVisible(true);
		
	}

	/**
	 * Iicializa las componentes del panel de control
	 */
	protected void initCtrlPanel() {
		
			JPanel p = new JPanel(new BorderLayout());
			p.setPreferredSize(new Dimension(100, 150));
			p.setBorder(BorderFactory.createTitledBorder("Status Messages"));
	
					statusArea = new JTextArea(5, 10);
					statusArea.setEditable(false);
	
				JScrollPane statusAreaScroll = new JScrollPane(statusArea);
			
			p.add(statusAreaScroll, BorderLayout.CENTER);
			
		addToCtrlArea(p);
		
		JPanel mainPanel = new JPanel(new BorderLayout());
		
		mainPanel.setBorder(BorderFactory.createTitledBorder("Player Information"));
		this.playerInfoTable = new PlayerInfoTableModel();
		JTable table = new JTable(playerInfoTable) {
		
			@Override
			public Component prepareRenderer(TableCellRenderer renderer, int row, int col) {
					Component comp = super.prepareRenderer(renderer, row, col);
					comp.setBackground(pieceColors.get(pieces.get(row)));
					return comp;
				}
		};
		
		table.setFillsViewportHeight(true);
		JScrollPane sp = new JScrollPane(table);
		mainPanel.setPreferredSize(new Dimension(100, 100));
		mainPanel.add(sp);
		addToCtrlArea(mainPanel);
		
		
		JPanel panela = new JPanel(new FlowLayout(FlowLayout.LEFT));
		panela.setBorder(BorderFactory.createTitledBorder("Piece Colors"));
		playerColorsCB = new JComboBox<Piece>();
		
		JButton setColorButton = new JButton("Choose Color");
		setColorButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Piece p = (Piece) playerColorsCB.getSelectedItem();
				ColorChooser c = new ColorChooser(new JFrame(),
				"Select Piece Color", pieceColors.get(p));
				boolean pintar = true;
				if (c.getColor() != null) {
					for (Piece h : pieces) {
						
						if (pieceColors.get(h).getRGB() == c.getColor().getRGB()) {
							pintar = false;
							JOptionPane.showMessageDialog(new JFrame(), "El color elegido está siendo usado!", "Error", JOptionPane.ERROR_MESSAGE);
						}
					}
					if(pintar){
						pieceColors.put(p, c.getColor());
						repaint();
					}
				}
			}
		});
		panela.add(playerColorsCB);
		panela.add(setColorButton);
		addToCtrlArea(panela);
		
		JPanel panelb = new JPanel(new FlowLayout(FlowLayout.LEFT));
		panelb.setBorder(BorderFactory.createTitledBorder("Player Modes"));
		
		modesCB = new JComboBox<PlayerMode>();
		modesCB.addItem(PlayerMode.MANUAL);
		
		if (randomPlayer != null) {
			modesCB.addItem(PlayerMode.RANDOM);
		}
		if (aiPlayer != null) {
			modesCB.addItem(PlayerMode.AI);
		}
		playerModesCB = new JComboBox<Piece>(new DefaultComboBoxModel<Piece>() {
			@Override
			public void setSelectedItem(Object o) {
				super.setSelectedItem(o);
				if (playerTypes.get(o) != PlayerMode.MANUAL) {
					modesCB.setSelectedItem(PlayerMode.AI);
				} 
				else {
					modesCB.setSelectedItem(PlayerMode.MANUAL);
				}
			}
		});
		
		JButton setModeButton = new JButton("Set");
		setModeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Piece p = (Piece) playerModesCB.getSelectedItem();
				PlayerMode m = (PlayerMode) modesCB.getSelectedItem();
				if(m == PlayerMode.AI)
					JOptionPane.showMessageDialog(new JFrame(), "Unimplemented Option!", "Error", JOptionPane.ERROR_MESSAGE);
				else{
					playerTypes.put(p, m);
					playerInfoTable.refresh();
				}
				if(p.equals(turn) && m == PlayerMode.RANDOM){
					decideMakeRandomMove(p);
				}
				//if(p == localPiece && m == PlayerMode.RANDOM){
					//decideMakeRandomMove(p);
				//}
			}
		});
		
		panelb.add(playerModesCB);
		panelb.add(modesCB);
		panelb.add(setModeButton);
		addToCtrlArea(panelb);
		
		movesPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		movesPanel.setBorder(BorderFactory.createTitledBorder("Automatic Moves"));
		
		randomButt = new JButton("Random");
		
		randomButt.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				decideMakeRandomMove(turn);
			}
		});
		
		aiButt = new JButton("Inteligente");
		
		aiButt.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(new JFrame(), "Unimplemented Option!", "Error", JOptionPane.ERROR_MESSAGE);
			}
		});
		
		movesPanel.add(randomButt);
		movesPanel.add(aiButt);
		
		addToCtrlArea(movesPanel);
		
		JPanel exit = new JPanel(new FlowLayout(FlowLayout.CENTER));
		
		this.quitButt = new JButton("Quit");
		
		quitButt.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				quit();
			}
		});
		exit.add(quitButt);
		
		if(localPiece == null){
			this.restartButt = new JButton("Restart");
			
			restartButt.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					ctrl.restart();
					playerInfoTable.refresh();
				}
			});
			exit.add(restartButt);
		}
		
		addToCtrlArea(exit);
		
		if(localPiece != null && localPiece != turn){
			noMostrarRandom (false);
		}
	}
	
	
	final protected void quit() {
		
		int n = JOptionPane.showOptionDialog(new JFrame(), "Are sure you want to quit?", "Quit",
				JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);

		if (n == 0) {
			
			try {
				ctrl.stop();
			} catch (GameError _e) {
			}
			
			setVisible(false);
			dispose();
			System.exit(0);	
		}	
	}
	

	/** GAME OBSERVER CALLBACKS **/

	@Override
	public void onGameStart(final Board board, final String gameDesc, final List<Piece> pieces, final Piece turn) {
			
			SwingUtilities.invokeLater(new Runnable() {
				@Override
				public void run() {
					handleGameStart(board, gameDesc, pieces, turn);
				}
				private void handleGameStart(Board board, String gameDesc, List<Piece>	pieces, Piece turn) {

					SwingView.this.setTitle("Board Games: " + gameDesc + (localPiece == null ? "" : " (" + localPiece + ")"));
					SwingView.this.gameDesc = gameDesc;
					SwingView.this.playerTypes = new HashMap<Piece, PlayerMode> ();
					SwingView.this.turn = turn;
					SwingView.this.board = board;
					SwingView.this.pieces = pieces;
					SwingView.this.inPlay = true;
					
					initGUI();
					initializePlayersTypes();
					initializePiecesColors();
					
					String msg = "Turn for:  ";
					if(localPiece != null && turn == localPiece){
						msg += "You (" + turn + ")";
						setActive(true);
					}
					else if(localPiece == null){
						msg += turn;
						setActive(true);

					}
					else{
						msg += turn;
						setActive(false);

					}
					addContentToStatusArea(msg);
					if(localPiece == null || localPiece == getTurn()){
						addContentToStatusArea(textoAyuda());
					}
				// handleTurnChange(turn);
				}		
			});
	}

	/**
	 * Inicializa a manual todos los jugadores
	 */
	private void initializePlayersTypes() {
		
		if(localPiece == null){
			for (Piece p : pieces) {
				if (playerTypes.get(p) == null) {
					playerTypes.put(p, PlayerMode.MANUAL);
					playerModesCB.addItem(p);
				}
			}
		}
		else{
			if(playerTypes.get(localPiece) == null){
				playerTypes.put(localPiece, PlayerMode.MANUAL);
				playerModesCB.addItem(localPiece);
			}
		}
	}
	
	/**
	 * Inicializa el color de cada jugador usando el iterador de colores
	 */
	private void initializePiecesColors() {
	
		playerColorsCB.removeAllItems();
		
		for (Piece p : pieces) {
			
			if (pieceColors.get(p) == null) {
				pieceColors.put(p, colorsIter.next());
			}
			playerColorsCB.addItem(p);
		}
	}
	
	/**
	 * Accede a numero de piezas que le quedna a un jugador
	 * @param p Jugador del que queremos saber el numero de piezas
	 * @return Devuelve el numero de piezas del jugadr indicado
	 */
	protected int getPieceCountAttt(Piece p){
		return board.getPieceCount(p);
	}

	@Override
	public void onGameOver(final Board board, final State state, final Piece winner) {
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				
				handleOnGameOver(board, state, winner);
			}
		});	
	}
	
	/**
	 * Metodo que gestiona el final de una partida
	 * @param board El tablero final que ha quedado al acabar el juego
	 * @param state Nos permite saber por que ha acabado el juego
	 * @param winner En caso de que haya jugador nos define cual ha sido
	 */
	private void handleOnGameOver(final Board board, final State state, final Piece winner){
		
		this.board = board;
		String msg = "";
		
		String say = "";
		
		if(state == State.Won){
			msg += "The Winner is:  " + winner;
			say += "The Winner is:  " + turn;
		}
		else{
			msg += "Draw";
			say += "Draw";
			
		}
		addContentToStatusArea(say);
		JOptionPane.showMessageDialog(new JFrame(), msg, "Game Over!", JOptionPane.INFORMATION_MESSAGE);
		noMostrarRandom(true);

	}
	@Override
	public void onMoveStart(Board board, Piece turn) {
		
	}

	@Override
	public void onMoveEnd(Board board, Piece turn, boolean success) {
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				handleOnMoveEnd(board, turn, success);
			}
			
		});	
	}
	
	/**
	 * 
	 * @param board
	 * @param turn
	 * @param success
	 */
	private void handleOnMoveEnd(Board board, Piece turn, boolean success){
		
		this.board = board;
		repaint();
	}

	@Override
	public void onChangeTurn(Board board, final Piece turn) {
		
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				handleOnChangeMove(board, turn);
			}
			
		});	
	}
	
	private void handleOnChangeMove(Board board, Piece turn){
		
		this.turn = turn;
		String msg = "Turn for:  ";
		if(localPiece != null && turn == localPiece){
			msg += "You (" + turn + ")";
			setActive(true);
			noMostrarRandom (true);
		}
		else if(localPiece == null){
			msg += turn;
			setActive(true);
			noMostrarRandom (true);
		}
		else{
			msg += turn;
			setActive(false);
			noMostrarRandom (false);
		}
		addContentToStatusArea(msg);
		
		if(playerTypes.get(turn) == PlayerMode.RANDOM || playerTypes.get(turn) == PlayerMode.AI){
			
			noMostrarRandom(false);
			setActive(false);
			decideMakeRandomMove(turn);		
		}
		else if(localPiece == null || localPiece == getTurn()){
			addContentToStatusArea(textoAyuda());
		}
	}
	
	protected abstract String textoAyuda();

	public void noMostrarRandom (boolean opt){
		
		movesPanel.setEnabled(opt);
		randomButt.setEnabled(opt);
		aiButt.setEnabled(opt);
		quitButt.setEnabled(opt);
	}

	@Override
	public void onError(String msg) {
		
		if (! inPlay || localPiece == null || turn.equals(localPiece )) {
			JOptionPane.showMessageDialog(new JFrame(), msg, "Error", JOptionPane.ERROR_MESSAGE);
		}
	}
	
	protected abstract void setActive(boolean active);
	protected abstract void decideMakeRandomMove(Piece turn);

}
