package tp2.game.gameobjects.characters;

import  tp2.game.*;
import tp2.game.gameobjects.*;

public abstract class Weapon extends GameObject{
 
	public Weapon(int f, int c, Game g, int l) {
		super(f, c, g, l);
	}
	
	public boolean receiveExplosiveAttack(int damage) {
		life -= damage;
		return true;
	}
	
	public boolean reachLeft() {return false;}
	public boolean reachRight() {return false;}
	public String info() { return null; }
	
}

