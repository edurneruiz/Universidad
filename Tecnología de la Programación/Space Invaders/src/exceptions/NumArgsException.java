package tp2.exceptions;

public class NumArgsException extends Exception {

	public NumArgsException() { super(); }
	public NumArgsException(String message){ super(message); }
	public NumArgsException(String message, Throwable cause){
		super(message, cause);
	}
	public NumArgsException(Throwable cause){ super(cause); }
	public NumArgsException(String message, Throwable cause,boolean enableSuppression, boolean writeableStackTrace){
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
