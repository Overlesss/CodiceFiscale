package codicefiscalePkg;

/** 
 * La classe CFexception permette la stampa di
 * errori caratteristici generati durante la generazione
 * od il controllo di un codice fiscale.
 * */
public class CFexception extends Exception {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private String err;
	
	
	/**
	 * @param mess contiene stringa errore da assegnare
	 * a err per costruire oggetto CFexception.
	 */
	public CFexception(final String mess) { err = mess; }
	
	
	/** @return stringa contenente messaggio dell'errore. */
    String estraiErrore() { return err; }
}
