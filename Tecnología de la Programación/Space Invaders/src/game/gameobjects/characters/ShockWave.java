package tp2.game.gameobjects.characters;

import  tp2.game.*;
import tp2.game.gameobjects.*;

public class ShockWave extends Weapon {

	private final static int d = 1;
	
	public ShockWave(int f, int c, Game g) {
		super(f, c, g, 0);
	}

	public boolean performAttack(GameObject other) {
		life = 0;
		return other.receiveShockWaveAttack(d);
	}
	
	public void move() {}
	public String toString() { return null; }

	public void ComputerAction() { }

	public String stringify() {	return "";}

}