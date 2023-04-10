//SPACE INVADERS - v3 - 
//AITOR ESTEBAN NÚÑEZ Y EDURNE RUIZ HUGUET

package tp2;

import tp2.controller.Controller;
import tp2.game.Level;

public class SpaceInvaders {

	public static void main(String[] args) {
		Level level =null;
		Controller controller;
		int seed = 1;
		
		try {
			if(args.length == 0) { throw new Exception("Must write the arguments");	}
			else {
				args[0] = args[0].toUpperCase();
				if ((args[0].equals("EASY")) || (args[0].equals("HARD")) || (args[0].equals("INSANE"))) { 
					switch(args[0]) {
					case "EASY":{ level = Level.EASY;}
					break;
					case "HARD":{ level = Level.HARD;}
					break;
					case "INSANE":{ level = Level.INSANE;}
					break;
					}
				}
				else {throw new Exception("Level must be one of: EASY, HARD, INSANE"); }
					
			try { seed = Integer.valueOf(args[1]);	}
			catch (NumberFormatException e) { System.out.println("Excepción al transformar la semilla, de tipo" + e);}
			}
		}
		catch(Exception e) { 
			System.out.println("Excepción al escribir los argumentos, de tipo" + e);
			System.exit(0);
		}	
		controller = new Controller(level, seed);
		controller.run();
	}
}


