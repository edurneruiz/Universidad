package tp2.controller.commands;

import tp2.game.Game;
import tp2.exceptions.*;

public class ExitCommand extends Command {
	
	public ExitCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	
	public boolean execute(Game game) {
		game.setDoExit(true);
		return false;
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if(commandWords.length != 1) { throw new CommandParseException(new NumArgsException(incorrectNumArgsMsg)); }
			else return this;
		}
		return null;
	}
}
