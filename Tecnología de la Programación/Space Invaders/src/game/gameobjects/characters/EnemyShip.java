package tp2.game.gameobjects.characters;

import  tp2.game.*;

public abstract class EnemyShip extends Ship {
	
	public EnemyShip(int f, int c, Game g, int l) {
		super(f, c, g, l);
	}
	
	public abstract String info();


}
