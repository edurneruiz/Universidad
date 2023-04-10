package tp2.exceptions;

public class CommandExecuteException extends Exception {
	
	public CommandExecuteException() { super(); }
	public CommandExecuteException(String message){ super(message); }
	public CommandExecuteException(String message, Throwable cause){
		super(message, cause);
	}
	public CommandExecuteException(Throwable cause){ super(cause); }
	public CommandExecuteException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}

}
