package tp2.game.gameobjects;

import tp2.game.*;
import tp2.exceptions.*;


public abstract class GameObject implements IAttack {
	protected int fila;
	protected int columna;
	protected Game game;
	protected int life;
	public static final String labelRefSeparator = " - ";
	protected int label = 0;
	
	public GameObject(int f,int c, Game g,int l) {
		fila = f;
		columna = c;
		game = g;
		life = l;
	}
	
	public int getFila() { return fila; }
	public int getColumna() { return columna; }
	public Game getGame() {return game;}
	public int getlife() {return life;}
	public void setlife(int n) {life = n;}
	public int getLabel() { return label; }
	public abstract void ComputerAction();
	public abstract String toString();
	public abstract void move() throws CommandExecuteException;
	public abstract boolean receiveExplosiveAttack(int damage);
	public abstract String stringify();
	public abstract String info();
	public abstract boolean reachLeft();
	public abstract boolean reachRight();
	
}
