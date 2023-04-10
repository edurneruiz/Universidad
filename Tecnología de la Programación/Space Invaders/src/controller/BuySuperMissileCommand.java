package tp2.controller.commands;

import tp2.game.Game;
import tp2.exceptions.*;

public class BuySuperMissileCommand extends Command{
	
	private final static String incorrectPoints= "Don't have enough points";

	public BuySuperMissileCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	public boolean execute(Game game) throws CommandExecuteException {
		if(game.getPlayer().getPoints() >= 20) {
			game.addContMissile(1);
			game.getPlayer().addPoints(-20);
		}
		else throw new CommandExecuteException("Failed to buy", new NotEnoughPointsException(incorrectPoints));
		return true;
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if(commandWords.length != 1) { throw new CommandParseException(new NumArgsException(incorrectNumArgsMsg)); }
			else return this;
		}
		return null;
	}

}
