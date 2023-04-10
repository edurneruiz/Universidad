package tp2.exceptions;

public class UnknownCommandException extends CommandParseException{
	
	public UnknownCommandException() { super(); }
	public UnknownCommandException(String message){ super(message); }
	public UnknownCommandException(String message, Throwable cause){
		super(message, cause);
	}
	public UnknownCommandException(Throwable cause){ super(cause); }
	public UnknownCommandException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
