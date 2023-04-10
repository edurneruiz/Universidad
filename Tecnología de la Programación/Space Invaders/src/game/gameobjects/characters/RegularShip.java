package tp2.game.gameobjects.characters;

import  tp2.game.*;

public class RegularShip extends AlienShip {

	protected final static int l = 2;
	protected final static String sc = "R";
	protected final static int p = 5;
	
	public RegularShip(int f, int c, Game g) {
		super(f, c, g, l);
	}

	public void ComputerAction() {
		if (IExecuteRandomActions.canGenerateExplosiveShip(game)) { game.changeExplosive(fila,columna,game); }
	}
	
	public String toString() {	return sc +"[" +  life + "]"; }
	public String info() {return "[" + sc + "]egular ship: Points:" + p + "- Harm: 0 - Shield:" + life; }	
	public String stringify() {
		int nextCycles =  game.getLevel().getVel() - (game.getCycles()% game.getLevel().getVel());
		return sc + ";" + fila +","+ columna +";" + life + ";" + nextCycles + ";" + AlienShip.direction;
	}
	
	public boolean receiveMissileAttack(int damage) {
		life-= damage;
		if (life <= 0) { 
			game.getPlayer().addPoints(p); 
			cont_aliens--;
		}
		return true;
	}

	public boolean receiveExplosiveAttack(int damage) {
		life -= damage;
		if (life == 0) { 
			game.getPlayer().addPoints(p);
			cont_aliens--;
		}
		return true;
	}
	
	public boolean receiveShockWaveAttack(int damage) {
		life-= damage;
		if (life <= 0) {
			game.getPlayer().addPoints(p);
			cont_aliens--; 
		}
		return true;
	}



}
