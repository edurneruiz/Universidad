package tp2.exceptions;

public class OffWorldException extends CommandExecuteException {
		
	public OffWorldException() { super(); }
	public OffWorldException(String message){ super(message); }
	public OffWorldException(String message, Throwable cause){
		super(message, cause);
	}
	public OffWorldException(Throwable cause){ super(cause); }
	public OffWorldException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}

}
