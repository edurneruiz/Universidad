package tp2.game.gameobjects;

import tp2.game.*;
import tp2.exceptions.*;
import tp2.game.gameobjects.characters.*;

public class GameObjectBoard{
	private static int MAX;
	private GameObject[] board;
	int cont;
	
	public GameObjectBoard(int x, int y) {
		MAX = x*y;
		board = new GameObject[MAX];
		cont = 0;
	}
	
	public int getCont() { return cont;	}

	public void delete(GameObject object) {
		int pos = buscarPos(object);
		if(pos != -1) {
			for(int i = pos; i < cont; i++) { board[i] = board[i+1]; }
			cont--;
		}
	}
	
	public void add(GameObject object) {
		if(cont < MAX-1) {
			board[cont] = object;
			cont++;
		}
	}
	public String toString(int x, int y) {
		String s = " ";
		int i = 0; 
		while (i < cont && (s == " ")) {
			s = (board[i].getFila() == x) && (board[i].getColumna() == y) ? board[i].toString() : " ";
			i++;
		}
		return s;
	}
	
	private int buscarPos(GameObject o) {
		int pos = -1;
		int i = 0;
		while(i < cont && pos == -1) {
			if(board[i].equals(o)) {pos = i;}
			i++;
		}
		return pos;
	}
	
	private int buscarPos(int f, int y) {
		int pos = -1;
		int i = 0;
		while(i < cont && pos == -1) {
			if(board[i].getFila() == f && board[i].getColumna() == y) {pos = i;}
			i++;
		}
		return pos;
	}
	
	public void initializeRegularShip(Game game, Level level) {
		int aux = cont;
		for(int i = 0; i < level.getCommon(); i++) {
			if (i < 4) { board[aux + i] = new RegularShip(1, i+3, game); }
			else { board[aux + i] = new RegularShip(2, i-1, game); } 
			cont++;
		}
		AlienShip.addContAliens(game.getLevel().getCommon());
	}
	
	public void initializeDestroyerShip(Game game, Level level) {
		int aux = cont;
		switch(level) {
		case EASY:{
			for(int i = 0; i < level.getDest(); i++) {
				board[aux + i] = new DestroyerShip(2, i+4, game);	
				cont++;
			}
		}
		break;
		case HARD:{
			for(int i = 0; i < level.getDest(); i++) {
				board[aux + i] = new DestroyerShip(3, i+4, game);	
				cont++;
			}
		}
		break;
		case INSANE:{
			for(int i = 0; i < level.getDest(); i++) {
				board[aux + i] = new DestroyerShip(3, i+3, game);	
				cont++;
			}
		}
		break;
		}
		AlienShip.addContAliens(game.getLevel().getDest());
	}

	public boolean existsLaser() { return Laser.ex; } 
	
	public void receiveShockWave(ShockWave sw) {  
		for (int i = 0; i < cont; i++) { sw.performAttack(board[i]);}
	}

	public void computerAction() {
		for(int i = 0; i <cont; i++) {
			board[i].ComputerAction();
		}
	}

	public void initializeOvni(Game game) {
		board[cont] = new Ovni(0,9,game);
		cont++;
	}
	
	public void update() throws CommandExecuteException {
		boolean reachedLeft = false, reachedRight = false;
		for(int i = 0; i < cont; i++) {
			board[i].move();
			if(board[i] != null && (board[i].reachLeft())) reachedLeft = true;
			if(board[i] != null && (board[i].reachRight())) reachedRight = true;
			for(int j = 0; j < cont; j++) {
				if(board[i] != null && i != j) { board[i].performAttack(board[j]) ;}
			}	
		}
		deleteDead();
		if(board[0].getGame().aliensMove()) { AlienShip.modificarDir(reachedLeft,reachedRight); }
		
	}

	private void deleteDead() {
		int i = 0;
		while (i < cont) {
			if(board[i].getlife() <= 0) { delete(board[i]); }
			else i++;
		}
	}
	
	public boolean noestaentablero(GameObject o) {
		return (buscarPos(o) == -1);
	}

	public void changeExplosive(int fila, int columna, Game game) {
		int i = buscarPos(fila,columna);
		board[i] = new ExplosiveShip(fila,columna,game);
	}

	public void explode(int f, int c) {
		if(onBoard(f,c)) {
			int i = buscarPos(f,c);
			if (i!=-1) board[i].receiveExplosiveAttack(ExplosiveShip.damage);
		}
	}
	
	private boolean onBoard(int f, int c) { return ((0 <= f) && (f <= Game.DIM_Y - 1) && (0 <= c) && (c <= Game.DIM_X - 1)); } 
	
	public String info() {
		String s = "";
		for (int i = 0; i < cont; i++) { 
			s = (board[i].info() != null) ? s +  board[i].info() + "\n" : s; 
		}
		return s;
	}

	public String stringify() {
		String s = "";
		for (int i = 0; i < cont; i++) {
			if (board[i].getlife() != 0) s = s + board[i].stringify() + "\n";
		}
		return s;
	}


}
