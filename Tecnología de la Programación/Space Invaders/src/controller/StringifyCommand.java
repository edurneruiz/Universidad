package tp2.controller.commands;

import tp2.exceptions.CommandParseException;
import tp2.exceptions.NumArgsException;
import tp2.game.*;

public class StringifyCommand extends Command {
	
	private static final String title = "— Space Invaders v2.0 —";

	public StringifyCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	
	public boolean execute(Game game) {
		PrinterTypes p = PrinterTypes.SERIALIZER;
		GamePrinter printer = p.getObject(game);
		System.out.println(title + "\n\n" + game.infoSerialized() + "\n" + game.getLevel().infoSerialized()+ "\n" + printer);
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
