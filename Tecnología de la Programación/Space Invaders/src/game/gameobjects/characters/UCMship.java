package tp2.game.gameobjects.characters;

import  tp2.game.*;
import tp2.exceptions.*;

public class UCMship extends Ship {
	private ShockWave sw;
	private int points;
	private int c;

	public UCMship(int f, int c, Game g) {
		super(f, c, g, 3);
		sw = new ShockWave(f,c,g);
		points = 0;
	}
	
	public int getPoints() { return points; }
	public ShockWave getSW() { return sw; }
	public void setSW() { sw.setlife(1);}
	public void setPasos (int p) { c= p;}
	public void addPoints(int p) { points+=p;}
	public void move() {};
	
	public void commandMove() throws CommandExecuteException {
		switch (dir) {
		case "LEFT": {
			if (columna -c >= 0) { columna = columna - c ; }
			else throw new CommandExecuteException("Failed to move:", new OffWorldException("Cannot perform move: ship too near border"));
		}
		break;
		case "RIGHT": {
			if (columna+c <= Game.DIM_Y) columna = columna + c; 
			else throw new CommandExecuteException("Failed to move:", new OffWorldException("Cannot perform move: ship too near border"));
		}
		break;
		}
	}

	public boolean isAlive() {	return life > 0; }
	public String stateToString() { return "Points: " + points + "\n" + "Life: " + life + "\n"; }
	public String toString() { return "^__^"; }
	public String stringify() { return "P;" + fila + "," + columna + ";" + life + ";" + points + ";" + sw.getlife() + ";" + game.getSMissile();	}

	public void ComputerAction() {}
	
	public boolean receiveBombAttack(int damage) {
		life -= damage;
		return true;
	}
	public boolean receiveExplosiveAttack(int damage) {
		life -= damage;
		return true;
	}
	
	public boolean reachLeft() {return false;}
	public boolean reachRight() {return false;}
	public String info() { return null; }

}
