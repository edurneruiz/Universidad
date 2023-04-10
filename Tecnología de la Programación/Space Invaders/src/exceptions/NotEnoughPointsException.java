package tp2.exceptions;

public class NotEnoughPointsException extends CommandExecuteException {

	public NotEnoughPointsException() { super(); }
	public NotEnoughPointsException(String message){ super(message); }
	public NotEnoughPointsException(String message, Throwable cause){
		super(message, cause);
	}
	public NotEnoughPointsException(Throwable cause){ super(cause); }
	public NotEnoughPointsException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
