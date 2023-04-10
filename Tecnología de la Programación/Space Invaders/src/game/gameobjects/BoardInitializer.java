package tp2.game.gameobjects;

import tp2.game.*;

public class BoardInitializer {
	
	private Level level;
	private GameObjectBoard board;
	private Game game;
	
	public GameObjectBoard initialize(Game game, Level level) {
		this.level = level;
		this.game = game;
		board = new GameObjectBoard(Game.DIM_X, Game.DIM_Y);
		board.initializeOvni(this.game);
		board.initializeRegularShip(this.game, this.level);
		board.initializeDestroyerShip(this.game, this.level);
		return board;
	}
	
}
