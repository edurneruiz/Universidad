package tp2.exceptions;

public class CommandParseException extends Exception {

	public final static String msg = "Failed to parse";
	
	public CommandParseException() { super(); }
	public CommandParseException(String message){ super(message); }
	public CommandParseException(String message, Throwable cause){
		super(message, cause);
	}
	public CommandParseException(Throwable cause){ super(msg, cause); }
	public CommandParseException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}

	
}
