package tp2.game.gameobjects.characters;

import  tp2.game.*;
import tp2.game.gameobjects.*;

public class Bomb extends Weapon{
	
	protected final static String sc = "B";
	private final static int d = 1;
	private DestroyerShip dest;

	public Bomb(int f, int c, Game g) {
		super(f, c, g, 1);
	}
	
	public void setDest(DestroyerShip d) {dest = d;}
	
	public boolean receiveMissileAttack(int damage) {
		life = 0;
		dest.desactivateBomb();
		return true; 
	}
	
	 public boolean performAttack(GameObject other) {
		 if (fila == other.getFila() && columna == other.getColumna()) {
			 if (other.receiveBombAttack(d)) {
				 life = 0;
				 return true;
			 }
		 }
		return false;
	 }
	 
	public void move() {
		if(fila == Game.DIM_Y-1) { 
			life = 0;
			dest.desactivateBomb();
		}
		else{ fila++; }	
	}

	public String toString() { return "."; }
	

	public void ComputerAction() {
		if(game.noestaentablero(this)) {
			if(IExecuteRandomActions.canGenerateRandomBomb(game)) { game.addObject(this); }
			else { dest.desactivateBomb();}
		}
	}

	public String info() { return null; }

	public String generateSerialRef() {
		return labelRefSeparator + dest.getLabel();
	}

	public String stringify() {
		 return sc + ";" + fila + "," + columna + generateSerialRef();
	}
	

}

