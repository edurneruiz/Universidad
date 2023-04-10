package tp2.exceptions;

public class NoShockwaveException extends CommandExecuteException {

	public NoShockwaveException() { super(); }
	public NoShockwaveException(String message){ super(message); }
	public NoShockwaveException(String message, Throwable cause){
		super(message, cause);
	}
	public NoShockwaveException(Throwable cause){ super(cause); }
	public NoShockwaveException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
