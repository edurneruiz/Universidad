package tp2.controller.commands;

import tp2.game.*;
import tp2.exceptions.*;

public class CommandGenerator  {
	
	private static Level level;

	private static Command[] availableCommands = {
			new ListCommand("LIST", "L", "[L]ist", "Prints the list of available ships."),
			new HelpCommand("HELP", "H", "[H]elp", "Prints the list of commands."),
			new ResetCommand("RESET", "R", "[R]eset", "Starts a new game"), 
			new ExitCommand("EXIT", "E", "[E]xit", "Terminates the program."),
			new UpdateCommand("UPDATE", "U", "[U]pdate", "Skips one cycle"),
			new ShootCommand("SHOOT", "S", "[S]hoot", "UCM-Ship launches a missile."),
			new MoveCommand("MOVE", "M", "[M]ove <left|right><1|2>", "Moves UCM-Ship to the indicated direction.",  "", 0),
			new ShockwaveCommand("SHOCKWAVE", "W", "shock[W]ave", "UCM-Ship releases a shock wave."),
			new BuySuperMissileCommand("BUY SUPERMISSILE", "B", "[B]uy supermissile", "Buys a supermissile for 20 points."),
			new StringifyCommand("SERIALIZE" , "ST" , "[ST]ringifier", "Prints the game as a plain text"),
			new ListPrintersCommand("LISTPRINTERS", "P", "List [P]rinters", "Print the list of available printers"),
			new SaveCommand("SAVE", "V" ,"Sa[V]e", "Saves the game")
	};
	
	public static void setLevel(Level l) {level = l;}
	public static Level getLevel() {return level;}
	
	public static Command parseCommand(String[ ] commandWords) throws CommandParseException {
		Command command;
		for(int i=0; i < availableCommands.length; i++) {
			command = availableCommands[i].parse(commandWords);
			if(command != null) {return command;}
		}
		return null;
	}
	
	public static String commandHelp() {
		String help = " ";
		for(int i=0; i < availableCommands.length; i++) {
			help = availableCommands[i].helpText() + help;
		}
		return help;	
	}
	
}
