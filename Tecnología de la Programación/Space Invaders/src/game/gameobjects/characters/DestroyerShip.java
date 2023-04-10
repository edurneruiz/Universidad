package tp2.game.gameobjects.characters;

import  tp2.game.*;

public class DestroyerShip extends AlienShip implements IExecuteRandomActions {

	protected final static int l = 1;
	protected final static String sc = "D";
	protected final static int p = 10;
	private Bomb bomb;
	
	public DestroyerShip(int f, int c, Game g) {
		super(f, c, g, l);
		bomb = null;
	}
	
	public String info() { return "[" + sc + "]estroyer ship: Points:" + p + "- Harm: 1 - Shield:" + life; }
	public String toString() { return sc +"[" +  life + "]"; }


	public void ComputerAction() {
		if (bomb == null) {
			bomb = new Bomb(fila,columna,game);
			bomb.setDest(this);
			bomb.ComputerAction();
		}
	}

	public void desactivateBomb() {	bomb = null; }
	
	public boolean receiveMissileAttack(int damage) {
		life-= damage;
		if(life <= 0) {
			game.getPlayer().addPoints(p);
			cont_aliens--;
		}
		return true;
	}

	public boolean receiveExplosiveAttack(int damage) {
		life -= damage;
		if(life <= 0) {
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
	
	private static int currentSerialNumber;

	private void initialiseLabelling() {
		currentSerialNumber = 1;
	}

	private String generateSerializingLabel() {
		label = currentSerialNumber;
		currentSerialNumber++;
		return labelRefSeparator + label;
	}
	
	
	
	public String stringify() {
		int nextCycles =  game.getLevel().getVel() - (game.getCycles()% game.getLevel().getVel());
		
		
		if (!game.isSerializing()) {
			game.setSerializing();
			initialiseLabelling();
		}
		return sc + ";" + fila +","+ columna +";" + life + ";" +nextCycles + ";" + AlienShip.direction + generateSerializingLabel();
	}
	
}
