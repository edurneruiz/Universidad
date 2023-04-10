package tp2.game.gameobjects.characters;

import  tp2.game.*;

public abstract class AlienShip extends EnemyShip{
    public static boolean landed;
	public static int cont_aliens;
	public static String direction = "LEFT";
	
	public AlienShip(int f, int c, Game g, int l) {
		super(f, c, g, l);
	}

	public static boolean haveLanded() { return landed;}
	public static boolean allDead() { return (cont_aliens == 0); }
	public static int getRemainingAliens() { return cont_aliens; }
	public static void setContAliens() { cont_aliens--;}
	public static void resetContAliens() { cont_aliens = 0; }
	public static String getDirection() {return direction;}
	public static void setDirection(String d) {direction = d;}
	public static void addContAliens(int c) { cont_aliens += c; }
	
	public void move() {
		if (game.aliensMove()) {
    		switch (direction) {
    		case "LEFT": columna--; //izq
    		break;
    		case "DOWN": fila++; //abajo
    		break;
    		case "RIGHT": columna++; //dcha
    		break;
    		}
    	}
		if (fila == Game.DIM_Y-1) { landed = true; }
	
	}	
	 
	public boolean reachLeft() { 
		if (columna == 0) { return true; }
		return false;
	}
	public  boolean reachRight() {
		if (columna == Game.DIM_X-1) { return true; }
		return false;
	}

	public static void modificarDir(boolean l, boolean r) {
		if(l|r) {
			String d = AlienShip.getDirection();
			if(d == "LEFT" && l) {AlienShip.setDirection("DOWN");}
			else if(d == "DOWN" && l) {AlienShip.setDirection("RIGHT");}
			else if	(d == "RIGHT" && r) {AlienShip.setDirection("DOWN");}
			else if(d == "DOWN" && r) {AlienShip.setDirection("LEFT");}
			
		}
	}
	
	
}