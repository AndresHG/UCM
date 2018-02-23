package es.ucm.fdi.tp.pr5.common;

import javax.swing.*;

import es.ucm.fdi.tp.basecode.bgame.Utils;
import es.ucm.fdi.tp.basecode.bgame.model.Board;
import es.ucm.fdi.tp.basecode.bgame.model.FiniteRectBoard;
import es.ucm.fdi.tp.basecode.bgame.model.Game.State;
import es.ucm.fdi.tp.basecode.bgame.model.GameObserver;
import es.ucm.fdi.tp.basecode.bgame.model.Observable;
import es.ucm.fdi.tp.basecode.bgame.model.Piece;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.*;


@SuppressWarnings("serial")
public abstract class BoardComponent extends JComponent{

	private int _CELL_HEIGHT = 50;
	private int _CELL_WIDTH = 50;

	private int rows;
	private int cols;
	private Board board;
	
	private HashMap<Piece, Color> pieceColors = new HashMap<Piece, Color>();
	private Iterator <Color> colorsIter = Utils.colorsGenerator () ;
	
	public enum Shapes{
		CIRCLE, RECTANGLE;
	}
	
	public BoardComponent(Board board){
		
		this.rows = board.getRows();
		this.cols = board.getCols();
		this.board = board;
		initGUI();
	}

	
	private void initGUI() {
		
		addMouseListener(new MouseListener() {

		    @Override
			public void mouseReleased(MouseEvent e) {
				BoardComponent.this.mouseReleased(e.getY()/_CELL_HEIGHT , e.getX()/_CELL_WIDTH, e.getButton());
			}

			@Override
			public void mousePressed(MouseEvent e) {
				BoardComponent.this.mousePressed(e.getY()/_CELL_HEIGHT , e.getX()/_CELL_WIDTH, e.getButton());
			}

			@Override
			public void mouseExited(MouseEvent e) {
				//System.out.println("Mouse Exited Component: " + "(" + e.getX() + "," + e.getY() + ")");
			}

			@Override
			public void mouseEntered(MouseEvent e) {
				//System.out.println("Mouse Entered Component: " + "(" + e.getX() + "," + e.getY() + ")");
			}

			@Override
			public void mouseClicked(MouseEvent e) {
				BoardComponent.this.mouseClicked(e.getY()/_CELL_HEIGHT , e.getX()/_CELL_WIDTH, e.getButton());			}
			
		});
		
		this.setSize(new Dimension(rows * _CELL_HEIGHT, cols * _CELL_WIDTH));
		
		repaint();
		
	}


	protected abstract void mouseClicked(int i, int j, int button);


	public void paintComponent(Graphics g) {
		
		super.paintComponent(g);

		_CELL_WIDTH  = this.getWidth()  / cols;
		_CELL_HEIGHT = this.getHeight() / rows;
		
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				drawCell(i, j, g);
		
	}

	private void drawCell(int row, int col, Graphics g) {
		
		int x = col * _CELL_WIDTH;
		int y = row * _CELL_HEIGHT;

		g.setColor(Color.LIGHT_GRAY);
		g.fillRect(x + 2, y + 2, _CELL_WIDTH - 4, _CELL_HEIGHT - 4);
		
		if(board.getPosition(row, col) != null){
			if(getPieceShape(board.getPosition(row,col)) == Shapes.CIRCLE){
				g.setColor(getPieceColor(board.getPosition(row,col)));
				g.fillOval(x + 4, y + 4, _CELL_WIDTH - 8, _CELL_HEIGHT - 8);
		
				g.setColor(Color.black);
				g.drawOval(x + 4, y + 4, _CELL_WIDTH - 8, _CELL_HEIGHT - 8);
			}
			else{
				
				g.setColor(Color.green);
				g.fillRect(x + 4, y + 4, _CELL_WIDTH - 8, _CELL_HEIGHT - 8);
		
				g.setColor(Color.black);
				g.drawRect(x + 4, y + 4, _CELL_WIDTH - 8, _CELL_HEIGHT - 8);			
			}
		}

	}

	public void setBoardSize(int rows, int cols) {
		repaint();
	}

	
	public void redraw(Board b){
		this.board = b;
		repaint();
		
	}
	
	protected abstract Color getPieceColor(Piece p);
	protected abstract  Shapes getPieceShape(Piece p);
	
	protected abstract void mouseReleased(int row, int col, int mouseButton);
	protected abstract void mousePressed(int row, int col, int mouseButton);
		

}
