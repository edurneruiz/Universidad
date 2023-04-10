package tp2.game.gameobjects.characters;

import  tp2.game.*;
import tp2.game.gameobjects.*;

public abstract class Ship extends GameObject {
	
	protected String dir;
	
	
	public Ship(int f, int c, Game g, int l) {
		super(f, c, g, l );
	}

	public int getVida() {return life;}
	public void setDir(String d) {dir = d.toUpperCase();}
}
