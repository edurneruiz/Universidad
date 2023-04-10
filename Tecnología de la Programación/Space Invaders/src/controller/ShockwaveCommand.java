package tp2.controller.commands;

import tp2.game.*;
import tp2.exceptions.*;
import tp2.game.gameobjects.characters.*;;

public class ShockwaveCommand extends Command {
	public ShockwaveCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	
	public boolean execute(Game game) throws CommandExecuteException {
		ShockWave sw = game.getPlayer().getSW();	
		if (sw.getlife() == 1) {
			game.attackShockWave(sw);
			continuar(game);
			return true;
		}
		else throw new CommandExecuteException("Failed to shoot", new NoShockwaveException("Cannot release shockwave: no shockwave available"));
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if(commandWords.length != 1) { throw new CommandParseException( new NumArgsException(incorrectNumArgsMsg)); }
			else return this;
		}
		return null;
	}
}
