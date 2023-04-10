package tp2.controller.commands;

import tp2.game.Game;
import tp2.exceptions.*;

public class UpdateCommand extends Command {

	public UpdateCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
		
	}

	public boolean execute(Game game) throws CommandExecuteException {
		continuar(game);
		return true;
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name) || commandWords[0].isEmpty()) {
			if(commandWords.length != 1) { throw new CommandParseException(new NumArgsException(incorrectNumArgsMsg)); }
			else return this;
		}
		return null;
	}
	
}