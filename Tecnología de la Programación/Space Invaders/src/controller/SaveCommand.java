package tp2.controller.commands;
import tp2.exceptions.CommandParseException;
import tp2.exceptions.NumArgsException;
import tp2.game.Game;
import tp2.game.GamePrinter;
import tp2.game.PrinterTypes;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SaveCommand extends Command {
	
	private static final String title = "— Space Invaders v2.0 —";
	private static String file;
	
	public SaveCommand(String name, String shortcut, String details, String help) {
		super(name, shortcut, details, help);
	}

	
	public boolean execute(Game game) throws IOException {
		BufferedWriter outChars = null;
		try {
		outChars = new BufferedWriter(new FileWriter(file + ".dat")); //excecpion al abrir o guardar
		
		String s = stringify(game);
	
		outChars.write(s); 
		
		System.out.println("Game successfully saved in file " + file + ".dat. Use the load command to reload it");
		} catch (IOException e) {		e.printStackTrace();	} 
		finally {
		if (outChars != null) { outChars.close(); }
		}
		return true;
	}

	public Command parse(String[] commandWords) throws CommandParseException {
		if (commandWords[0].toUpperCase().equals(shortcut) || commandWords[0].toUpperCase().equals(name)) {
			if(commandWords.length > 2) { throw new CommandParseException(new NumArgsException(incorrectNumArgsMsg));  }
			else {
				if (commandWords.length == 1) { file = "archivo"; } 
				if(commandWords.length == 2) { file = commandWords[1]; } 
				return this;
			}
		}
		return null;
	}
	
		
	public String stringify(Game game) {
		PrinterTypes p = PrinterTypes.SERIALIZER;
		GamePrinter printer = p.getObject(game);
		return title + "\n\n" + game.infoSerialized() + "\n" + game.getLevel().infoSerialized()+ "\n" + printer;
	}
}
