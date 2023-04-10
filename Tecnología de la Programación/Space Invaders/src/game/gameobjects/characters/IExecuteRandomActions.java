package tp2.game.gameobjects.characters;

import  tp2.game.*;

public interface IExecuteRandomActions {
	static boolean canGenerateRandomOvni(Game game){
		return game.getRandom().nextDouble() < game.getLevel().getOvni();
	}
	
	static boolean canGenerateRandomBomb(Game game){
		return game.getRandom().nextDouble() < game.getLevel().getFrec();
	}
	
	static boolean canGenerateExplosiveShip(Game game) {
		return game.getRandom().nextDouble() < game.getLevel().getExplosive();
	}
	
}