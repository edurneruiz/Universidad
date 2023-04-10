package tp2.game;

public enum Level {
	EASY(4, 2, 0.1, 3, 0.5, 0.05),
	HARD(8, 2, 0.3, 2, 0.3, 0.05),
	INSANE(8, 4, 0.5, 1, 0.1, 0.05);
	
	private final int common;
	private final int destructor;
	private final double frec;
	private final int vel;
	private final double ovni;
	private final double explosive;
	
	Level(int c, int d, double f, int v, double o, double exp) {
		common = c;
		destructor = d;
		frec = f;
		vel = v;
		ovni = o;
		explosive = exp;
	}
	
	public int getCommon() { return common; }
	public int getDest() { return destructor; }
	public double getFrec() { return frec; }
	public int getVel() { return vel; }
	public double getOvni() { return ovni; }
	public double getExplosive() { return explosive; }
	
	public String toString() { return (this == EASY) ? "EASY" : (this == HARD) ? "HARD" : "INSANE"; }
	public String infoSerialized() { return "L;" + this.toString();}
	
}

