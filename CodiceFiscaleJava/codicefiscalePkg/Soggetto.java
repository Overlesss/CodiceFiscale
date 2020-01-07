package codicefiscalePkg;


/** 
 * La classe Soggetto permette di rappresentare
 * una persona tramite i suoi cati caratteristici:
 * Codice fiscale, Identificativo, Sesso e dati di Nascita.
 * */
public class Soggetto {
	private CodiceFiscale cf = new CodiceFiscale();
	private Identificativo nominativo = new Identificativo();
	private Sesso sesso = new Sesso();
	private Nascita datiNascita = new Nascita();

	
	public Soggetto() {}
	
	
	public Soggetto(final CodiceFiscale c) {
		cf = c;		
	}


	//costruttore di copia
	public Soggetto(final Soggetto s) {
		cf = s.cf;
		nominativo = s.nominativo;
		sesso = s.sesso;
		datiNascita = s.datiNascita;
	}

	
	/**
	 * Assegnazione campo dati di Soggetto di tipo
	 * @param pDP
	 */
	public void assegna(DatiPersona pDP) {
		if(pDP instanceof Sesso) {
			Sesso pS = (Sesso) pDP;
			if(pDP instanceof Nascita) {
				Identificativo pI = (Identificativo) pDP;
				nominativo = pI;
			}
	        else sesso = pS;
	        return;
	    }
		if(pDP instanceof Nascita) {
			Nascita pN = (Nascita) pDP;
			datiNascita = pN;
	        return;
	    }
		if(pDP instanceof CodiceFiscale) {
			CodiceFiscale pCf = (CodiceFiscale) pDP;
	        cf = pCf;
	        return;
	    }
	}
	
	
	
	/**
	 * Crea oggetto relativo a TD di
	 * @param pDP calcolato da 
	 * @param cod che e' una sottostringa del codice fiscale.
	 * @throws CFexception se tentativo di creazione oggetto fallisce.
	 */
	public DatiPersona creaDaCodice(DatiPersona pDP, final String cod) throws CFexception {
	    pDP.creaDaCodice(cod);
	    if(pDP instanceof Nascita) {
	    	Nascita pN = (Nascita) pDP;
	    	datiNascita = pN;
	        return datiNascita;
	    }
	    if(pDP instanceof Sesso) {
	    	Sesso pS = (Sesso) pDP;
	    	sesso = pS;
	        return sesso;
	    }
	    return pDP;
	}
	
	
	/**
	 * @return stringa che rappresenta parte di codice fiscale relativa a TD di
	 * @param pDP
	 */
	static public String generaCodice(DatiPersona pDP) {
		if(pDP instanceof Nascita) {
			Nascita pN = (Nascita)pDP;	
			Data pD = new Data(pN);
			return pD.generaCodice() + pN.generaCodice();
		}
	    return pDP.generaCodice();
	}
	
	
	/**
	 * @throws CFexception se metodo controllo() di TD di
	 * @param pDP trova valori non validi.
	 */
	static public void controllo(DatiPersona pDP) throws CFexception {
	    pDP.controllo();
	}
	
	
	/**
	 * @return stringa generata da metodo toString() di TD di
	 * @param pDP.
	 */
	static public String estraiDati(final DatiPersona pDP) {
	    return pDP.toString();
	}
	
	
	/**
	 * overrides java.lang.Object.toString
	 * @return stringa descrittiva dei campi dati di un Soggetto
	 */
	public String toString() {
		String s = "";
		if(cf.toString() != "") { s += " codice fiscale: " + estraiDati(cf) + "\n"; }
	    if(nominativo.estraiCognome() != "") { s += " nome e cognome: " + estraiDati(nominativo) + "\n"; }
	    if(sesso.estraiGenere() != '0') { s += " sesso: " + estraiDati(sesso) + "\n"; }
	    if(datiNascita.estraiGiorno() != 0 && datiNascita.estraiLuogo() != "") { s += estraiDati(datiNascita) + "\n"; }
	    return s;
	}

}
