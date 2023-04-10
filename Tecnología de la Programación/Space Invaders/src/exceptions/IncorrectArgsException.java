package tp2.exceptions;

public class IncorrectArgsException extends CommandParseException {
	public IncorrectArgsException() { super(); }
	public IncorrectArgsException(String message){ super(message); }
	public IncorrectArgsException(String message, Throwable cause){
		super(message, cause);
	}
	public IncorrectArgsException(Throwable cause){ super(msg, cause); }
	public IncorrectArgsException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
