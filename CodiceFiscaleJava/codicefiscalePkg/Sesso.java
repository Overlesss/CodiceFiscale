package codicefiscalePkg;


/**
 * La classe Sesso rappresenta il genere
 * di una Persona. Contiene funzioni utili per il controllo e
 * il calcolo del codice fiscale e del suo inverso.
 */
public class Sesso extends DatiPersona {
	private char genere;

	public Sesso() { this('0'); }

	public Sesso(char s) { genere = s; }
	
	
	//costruttore di copia
	public Sesso(final Sesso x) {
		genere = x.genere;
	}

	
	/** @return carattere che rappresenta il genere */
	public char estraiGenere() {
		return genere;
	}
		
	
	/**
	 * @param cod contiene sottostringa del codice fiscale che identifica giorno di nascita e sesso.
	 * Se valore compreso tra 0 e 31 allora genere maschile,
	 * altrimenti genere femminile.
	 */
	public void creaDaCodice (final String cod) throws CFexception {
	    //validita' data (e quindi sesso) controllata nei precedenti controlli su Data
	
	    //estrazione codice giorno da codice fiscale (sulla base del quale e' calcolato il sesso)
		int n = Integer.parseInt(cod);
	    if(n>0 && n<=31) genere = 'M';
	        else genere = 'F'; //da metodo Nascita.creaDaCodice, l'altro intervallo e' necessariamente n>40&&n<=71
	}


	/**
	 * @return "40" se genere femminile, "0" se genere maschile.
	 * Rappresenta il valore da sommare a giorno di nascita
	 * nel codice fiscale.
	 */
	public String generaCodice() {
	    if(genere == 'f' || genere == 'F') return "40";
	    else return "0";
	}

	
	/** @throws CFexception se genere diverso da m, oppure M, oppure f, oppure F. */
	public void controllo () throws CFexception {
	    if(genere!='m' && genere!='f' && genere!='M' && genere!='F') throw new CFexception("Sesso non corretto.");
	}
	
	
	/**
	 * overrides java.lang.Object.toString
	 * @return stringa descrittiva del campo dati di Sesso
	 */
	public String toString() {
	    if(genere == 'M' || genere == 'm') return "MASCHIO";
	    else return "FEMMMINA";
	}
}