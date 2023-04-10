package tp2.controller.commands;

import tp2.game.Game;
import tp2.exceptions.*;

public class MoveCommand extends Command {
	
	private String dir;
	private int pasos;
	
	public MoveCommand(String name, String shortcut, String details, String help, String d, int p) {
		super(name, shortcut, details, help);
		dir = d;
		pasos = p;
	}

	public boolean execute(Game game) throws CommandExecuteException {
		game.getPlayer().setDir(dir);
		game.getPlayer().setPasos(pasos);
		game.getPlayer().commandMove();	
		continuar(game);
		return true;
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if (commandWords.length != 3) { throw new CommandParseException(new NumArgsException(incorrectNumArgsMsg));}
			else if (direccion(commandWords[1]) && pasos(commandWords[2])) {
				dir = commandWords[1];
				try { pasos = Integer.valueOf(commandWords[2]); }
				catch (NumberFormatException e) { System.out.println("Excepción al introducir el numero de pasos, de tipo" + e);}
				return this; 
			}
			else throw new CommandParseException(new IncorrectArgsException(incorrectArgsMsg));
		}
		return null;
	}
	
	
    private boolean direccion(String comando) { return comando.toUpperCase().contentEquals("LEFT") || comando.toUpperCase().contentEquals("RIGHT"); }
    private boolean pasos(String casillas) { return (casillas.toUpperCase().equals("1")) || (casillas.toUpperCase().equals("2")); }

	
}
