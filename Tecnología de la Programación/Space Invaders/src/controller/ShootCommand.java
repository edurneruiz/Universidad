package tp2.controller.commands;

import tp2.game.*;
import tp2.exceptions.*;
import tp2.game.gameobjects.characters.*;

public class ShootCommand extends Command {

	boolean sm;
	
	public ShootCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	
	public boolean execute(Game game) throws CommandExecuteException {
		if (!sm) {
			if (game.existsLaser()) throw new CommandExecuteException("Failed to shoot", new MissileInFlightException("Cannot fire missile: missile already exists on board"));
			else {
				Laser l = new Laser(0 , 0, game);
				l.initLaser(game.getPlayer());
				game.addObject(l);
				continuar(game);
				return true;
			}
		}
		else {
			if (game.getSMissile() == 0) throw new CommandExecuteException("Failed to shoot", new NoSuperMissileException("Cannot fire supermissile: you don't own any supermissile"));
			else {
				SuperMissile m = new SuperMissile(0,0,game);
				m.initSM(game.getPlayer());
				game.addObject(m);
				game.addContMissile(-1);
				sm = false;
				continuar(game);
				return true;
			}
		}
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if(commandWords.length > 2) { throw new CommandParseException(new NumArgsException(incorrectNumArgsMsg));  }
			else {
				if(commandWords.length == 2) {
					if (commandWords[1].toUpperCase().equals("SUPERMISSILE")) { 
						sm = true; 
					}
					else throw new CommandParseException(new UnknownCommandException(unknownCommandMsg));
				}
				return this;
			}
		}
		return null;
	}

}
