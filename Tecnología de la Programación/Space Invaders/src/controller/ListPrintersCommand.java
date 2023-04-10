package tp2.controller.commands;

import tp2.exceptions.CommandParseException;
import tp2.exceptions.NumArgsException;
import tp2.game.Game;
import tp2.game.PrinterTypes;

public class ListPrintersCommand extends Command {

	public ListPrintersCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	
	public boolean execute(Game game) {
		String s = PrinterTypes.printerHelp(game);
		System.out.println(s); 
		return true;
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if(commandWords.length != 1) { throw new CommandParseException("Failed to parse", new NumArgsException(incorrectNumArgsMsg)); }
			else return this;
		}
		return null;
	}

}
