package tp2.game.gameobjects.characters;

import  tp2.game.*;
import tp2.game.gameobjects.*;

public class Laser extends Weapon {
	
	protected static final String sc = "M";
	private final static int d = 1;
	public static boolean ex;

	public Laser(int f, int c, Game g) {
		super(f, c, g, 0);
		ex = false;
	}

	public void initLaser(UCMship u) {
		fila = u.getFila();
		columna = u.getColumna();
		life = 1;
		ex = true;
	}
	
	public boolean performAttack(GameObject other) {
		 if (fila == other.getFila() && columna == other.getColumna()) {
			 if(other.receiveMissileAttack(d)) {
				 life = 0;
				 ex = false;
				 return true;
			 }
		}
		return false;
	}


	public boolean receiveBombAttack(int damage) {
		life-=damage;
		if (life <= 0) ex = false;
		return true;
	}

	public void move() {
		if(fila == 0) { 
			life = 0;
			ex = false;
		}
		else{ fila--; }		
	}

	public String toString() { return "oo"; }
	public String stringify() { return sc + ";" + fila + "," + columna; }

	
	public void ComputerAction() {}

	

}