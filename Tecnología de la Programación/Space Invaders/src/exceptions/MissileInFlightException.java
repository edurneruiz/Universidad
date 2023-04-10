package tp2.exceptions;

public class MissileInFlightException extends CommandExecuteException {

	public MissileInFlightException() { super(); }
	public MissileInFlightException(String message){ super(message); }
	public MissileInFlightException(String message, Throwable cause){
		super(message, cause);
	}
	public MissileInFlightException(Throwable cause){ super(cause); }
	public MissileInFlightException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
