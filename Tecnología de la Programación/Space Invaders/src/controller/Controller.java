package tp2.controller;

import java.io.IOException;
import java.util.Random;
import java.util.Scanner;
import tp2.controller.commands.*;
import tp2.exceptions.*;
import tp2.game.*;


public class Controller {
	protected static final String unknownCommandMsg = "Unknown command";
	private Game game;
	private Scanner in = new Scanner(System.in);

	protected static final String PROMPT = "Command -> ";
	
	private GamePrinter printer;
	
	public Controller(Level level, int seed) {
		Random rnd = new Random(); 
		game = new Game(level, rnd);
		printer = PrinterTypes.BOARDPRINTER.getObject(game);
	}
	
	public void setGame(Game g) { game = g; }
	
	public void run() {
		
		System.out.println(printer);
		System.out.println(game.infoToString());
	
		while (!game.isFinished()){
			System.out.println(PROMPT);
			String[] words = in.nextLine().toLowerCase().trim().split ("\\s+");
		try {
			Command command = CommandGenerator.parseCommand(words);
			if (command != null) {
				if (command.execute(game)) {
					System.out.println(printer);
					if (!game.isFinished()) System.out.println(game.infoToString());
				}
			}
			else { throw new CommandParseException(new UnknownCommandException(unknownCommandMsg));}
		}
		catch (CommandParseException | CommandExecuteException ex) { System.out.format(ex.getMessage() + "\n" + "Cause of Exception: " + ex.getCause() + "\n"); }
		catch (IOException e) {	e.printStackTrace();}
		}
	}
}
