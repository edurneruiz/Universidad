package tp2.game;
import java.util.Random;
import tp2.exceptions.*;
import tp2.game.gameobjects.*;
import tp2.game.gameobjects.characters.*;


public class Game {
	public final static int DIM_X = 9;
	public final static int DIM_Y = 8;
	private int currentCycle;
	private Random rand;
	private Level level;
	GameObjectBoard board;
	private UCMship player;
	private boolean doExit;
	private BoardInitializer initializer;
	private int contSuperMissile;
	private boolean serializing = false;

	
	public Game (Level level, Random random){
		this.rand = random;
		this.level = level;
		initializer = new BoardInitializer();
		initGame();
	}
	
	public void initGame () {
		contSuperMissile = 0;
		currentCycle = 0;
		AlienShip.resetContAliens();
		board = initializer.initialize(this, level);
		player = new UCMship(DIM_Y - 1, DIM_X/2, this);
		board.add(player);
	}
 
	public void addContMissile(int d) { contSuperMissile += d;}
	public int getSMissile() {return contSuperMissile;}
	public Random getRandom() {return rand;}
	public Level getLevel() {return level;}
	public void setDoExit(boolean e) { doExit = e; }
	public UCMship getPlayer() { return player;	}
	public int getCycles() { return currentCycle; }
	public boolean aliensMove() { return currentCycle % level.getVel() == 0; }
	
	public boolean existsLaser() { return board.existsLaser();}
	public void reset() {initGame();}
	public void addObject(GameObject object) {board.add(object);}
	public String positionToString(int x, int y) {return board.toString(x, y);}
	public boolean isFinished() {return playerWin() || aliensWin() || doExit;}
	public boolean aliensWin() {return !player.isAlive () || AlienShip.haveLanded();}
	private boolean playerWin () {return AlienShip.allDead();}
	public void update() throws CommandExecuteException {	
		board.computerAction();
		board.update();
		System.out.println(getWinnerMessage());
		currentCycle++;
	}
	public boolean isOnBoard(int x, int y) { return x >= 0 && y >= 0 && x < DIM_X && y < DIM_Y;	}
	public void exit() {doExit = true;	}
	public String infoToString() {	return "Cycles: " + currentCycle + "\n" + player.stateToString() +	"Remaining aliens: " + (AlienShip.getRemainingAliens()) + "\n" + "ShockWave:" + this.getPlayer().getSW().getlife() + "\n" + "SuperMissiles:" + this.contSuperMissile;	}
	public String getWinnerMessage () {
		if (this.playerWin()) return "Player win!";
		else if (this.aliensWin()) return "Aliens win!";
		else if (doExit) return "Player exits the game";
		return "";
	}
	
	public void delete(GameObject object) { board.delete(object); }

	public String characterAtToString(int f, int c) { return board.toString(f, c); } // si en (f, c) hay un elemento --> lo dibuja	
	
	public String infoBoard() { return board.info(); }
	
	public void attackShockWave(ShockWave sw) { board.receiveShockWave(sw); }
	
	public boolean noestaentablero(GameObject o) { return board.noestaentablero(o); }

	public void changeExplosive(int fila, int columna, Game game) { board.changeExplosive(fila,columna, game); }
	
	public void explode(int f, int c) { board.explode(f,c);}
	
	public String stringify() {	
		serializing = false;
		return board.stringify();
	}
	
	public String infoSerialized() { return "G;" + currentCycle;}
	
	public void setSerializing() { serializing = true; }
	
	public boolean isSerializing() { return serializing; }

	
}
	
