package tp2.exceptions;

public class NoSuperMissileException extends CommandExecuteException {
	public NoSuperMissileException() { super(); }
	public NoSuperMissileException(String message){ super(message); }
	public NoSuperMissileException(String message, Throwable cause){
		super(message, cause);
	}
	public NoSuperMissileException(Throwable cause){ super(cause); }
	public NoSuperMissileException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
