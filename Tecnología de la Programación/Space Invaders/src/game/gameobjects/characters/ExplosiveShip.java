package tp2.game.gameobjects.characters;

import tp2.game.Game;

public class ExplosiveShip extends RegularShip {
	
	public final static int damage = 1;
	public static String sc = "E";

	public ExplosiveShip(int f, int c, Game g) {
		super(f, c, g);
	}

	public String toString() { return sc + "[" + life + "]"; }
	public String info() { return "[" + sc + "]xplosive ship: Points:" + p + "- Harm:" + damage + "- Shield: " + life; }
	public String stringify() {
		int nextCycles =  game.getLevel().getVel() - (game.getCycles()% game.getLevel().getVel());
		return sc + ";" + fila +","+ columna +";" + life + ";" + nextCycles + ";" + AlienShip.direction;
	}
	
	public boolean receiveMissileAttack(int damage) {
		life-= damage;
		if(life <= 0) {
			explode();
			game.getPlayer().addPoints(p);
			cont_aliens--;
		}
		return true;
	}
	
	public boolean receiveShockWaveAttack(int damage) {
		life-= damage;
		if(life <= 0) {
			explode();
			game.getPlayer().addPoints(p);
			cont_aliens--;
		}
		return true;
	}

	public boolean receiveExplosiveAttack(int damage) {
		life -= damage;
		if (life == 0) { 
			explode();
			game.getPlayer().addPoints(p);
			cont_aliens--;
		}
		return true;
	}
	
	private void explode() {
	 for (int c = columna - 1; c < columna + 2; c++) {
		 for (int f = fila - 1; f < fila + 2; f++) {
				 if (c != columna || f != fila) game.explode(f,c);
			 }
		 }
	}
	
	public void ComputerAction() {}
	
}
 

 

 
 