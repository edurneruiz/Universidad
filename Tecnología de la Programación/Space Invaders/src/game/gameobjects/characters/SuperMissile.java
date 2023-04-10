package tp2.game.gameobjects.characters;

import tp2.game.Game;
import tp2.game.gameobjects.GameObject;

public class SuperMissile extends Weapon {
	
	protected static final String sc = "X";
	private static final int dmg = 2;

	public SuperMissile(int f, int c, Game g) {
		super(f, c, g, 0);
	}
	public void initSM(UCMship u) {
		fila = u.getFila();
		columna = u.getColumna();
		life = 1;
	}
	
	public String toString() { return "00";	}
	public String stringify() { return sc + ";" + fila + "," + columna; }

	public void move() {
		if(fila == 0) { life = 0; }
		else{ fila--; }		
	}
	
	public boolean performAttack(GameObject other) {
		 if (fila == other.getFila() && columna == other.getColumna()) {
			 if(other.receiveMissileAttack(dmg)) {
				 life = 0;
				 return true;
			 }
		}
		return false;
	}
	
	public boolean receiveBombAttack(int damage) {
		life -= damage;
		return true;
	}
	
	public void ComputerAction() {}
}
