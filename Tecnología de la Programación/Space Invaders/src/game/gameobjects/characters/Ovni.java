package tp2.game.gameobjects.characters;

import  tp2.game.*;

public class Ovni extends EnemyShip implements IExecuteRandomActions {
	
	protected final static int l = 1;
	protected final static String sc = "O";
	protected final static int p = 25;
	public boolean ex;
	
	public Ovni(int f, int c, Game g) {
		super(f, c, g, l);
		ex = false;
	}
	
	private void initOvni() {
		ex = false;
		life = 1;
		columna = 9;
		game.getPlayer().setSW();
	}
	
	public String info() { 
		if (life > 0) return "[" + sc + "]vni: Points:" + p + "- Harm: 1 - Shield:" + l; 
		else return "";
	}
	public String toString() { return sc +"[" +  life + "]"; }
	public String stringify() {
		if (columna != 9) return sc + ";" + fila + "," + columna + ";" + life;
		else return "";
	}

	public void ComputerAction() {
		if(IExecuteRandomActions.canGenerateRandomOvni(game)) {
			life = l;
			ex = true;
		}
	}

	public void move() {
		 if (ex) {columna--;}
		 if (columna < 0) { 
			 ex = false;
			 columna = 9;
		 }
	}
	
	
	public boolean receiveMissileAttack(int damage) {
		life -= damage;
		if(life <= 0) {
			initOvni();	
			game.getPlayer().addPoints(Ovni.p);
		}
		return true;
	}
	
	public boolean receiveExplosiveAttack(int damage) {
		life -= damage;
		if(life <= 0) { 
			initOvni();
			game.getPlayer().addPoints(p); 
		}
		return true;
	}

	public boolean reachLeft() { return false;}

	public boolean reachRight() {return false;}

	
}
