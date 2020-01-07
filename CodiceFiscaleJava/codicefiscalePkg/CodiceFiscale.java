package codicefiscalePkg;


/**
 * La classe CodiceFiscale rappresenta il codice fiscale identificativo
 * di una Persona. Contiene funzioni utili per il controllo della validita',
 * del calcolo del codice, e del suo inverso.
 */
public class CodiceFiscale extends DatiPersona {
	private String codice;

	private static final String ALFABETO = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	
	public CodiceFiscale() { this(""); }

		
	public CodiceFiscale(String c) {
		codice = c;
	}
		
	
	//costruttore di copia
	public CodiceFiscale(final CodiceFiscale c) {
		codice = c.codice;
	}
	

	/*
	 * @param dispari contiene i caratteri di posizioni dispari in codice.
	 * @return la somma dei valori assegnati a ciascun carattere
	 * {@link https://it.wikipedia.org/wiki/Codice_fiscale#Generazione_del_codice_fiscale}
	 */
	private static int cinDispari(String dispari) {
	    int sum = 0; //conterra' la somma dei corrispondenti valori dei caratteri di dispari
	    final int [] NUMERI = {1, 0, 5, 7, 9, 13, 15, 17, 19, 21};
	    final String ALFABETO_DISPARI = ("BAKPLCQDREVOSFTGUHMINJWZYX");
	    for(int it = 0; it < dispari.length(); ++it) {
	    	char c = dispari.charAt(it); //estrazione carattere da dispari in posizione it
	        if(ALFABETO.indexOf(c) != -1)
	            //il carattere c e' una lettera dell'alfabeto
	        	sum += ALFABETO_DISPARI.indexOf(c);
	        else {
	            //il carattere c it e' una cifra
	            int n = Character.getNumericValue(c);
	            sum += NUMERI[n];
	        }
	     }
	    return sum;
	}
	
	
	/*
	 * @param pari contiene i caratteri di posizioni pari in codice.
	 * @return la somma dei valori assegnati a ciascun carattere
	 * {@link https://it.wikipedia.org/wiki/Codice_fiscale#Generazione_del_codice_fiscale}
	 */	private static int cinPari(String pari) {
	    int sum = 0; //conterra' la somma dei corrispondenti valori dei caratteri di pari
	    for(int it = 0; it < pari.length(); ++it) {
	    	char c = pari.charAt(it); //estrazione carattere da pari in posizione it
	        if(ALFABETO.indexOf(c) != -1)
	            //il carattere c e' una lettera dell'alfabeto
	        	sum += ALFABETO.indexOf(c);
	        else {
	            //il carattere c it e' una cifra
	            int n = Character.getNumericValue(c);
	            sum += n;
	        }
	    }
	    return sum;
	}
	
	
	/** @return sottostringa di codice che rappresenta Identificativo */
	public String estraiCodIdentificativo() { return codice.substring(0,6);	}
	
	/** @return sottostringa di codice che rappresenta anno di nascita */
	public String estraiCodAnno() { return codice.substring(6,8); }
	
	/** @return sottostringa di codice che rappresenta mese di nascita */
	public char estraiCodMese() { return codice.charAt(8); }
	
	/** @return sottostringa di codice che rappresenta giorno di nascita e Sesso */
	public String estraiCodGiornoSesso() { return codice.substring(9,11); }
	
	/** @return sottostringa di codice che rappresenta luogo di nascita (codice belfiore) */
	public String estraiCodLuogo() { return codice.substring(11,15); }
	
	/** @return sottostringa di codice che rappresenta CIN */
	public char estraiCin() { return codice.charAt(15); }
	
		
	/**
	 * 
	 * @param cin_atteso e' il CIN calcolato dai primi 15 caratteri di codice
	 * @throws CFexception se cin_atteso diverso dall'ultimo carattere di codice.
	 */
	public void controlloCin(final String cin_atteso) throws CFexception {
		//codice fiscale di 16 caratteri, il carattere in ultima posizione e' il CIN
	    //controllo corrispondenza CIN del codice fiscale rispetto al parametro passato alla funzione
	    final String cin_attuale = codice.substring(15); //estrazione carattere da codice in posizione 15
	    if(cin_attuale.equals(cin_atteso) == false) throw new CFexception ("Codice fiscale non valido.");
	}

	
	/** @param x contiene la stringa da assegnare a codice, se divero dal valore corrente di codice. */
	public void creaDaCodice(final String x) throws CFexception {
	    if(codice != x) codice = x;
	}

	
	/** @return stringa contenente CIN calcolato dai primi 15 caratteri di codice. */
	public String generaCodice() {
	    String cf_estratto = codice;
	    //se codice ha 16 caratteri, elimino ultimo carattere per calcolare CIN
	    if(cf_estratto.length() == 16)
	    	cf_estratto = cf_estratto.substring(0, cf_estratto.length()-1);
	    
	    //calcolo CIN sulla base dei primi 15 caratteri di codice
	    String pari = "";
	    String dispari = "";
	    for(int i = 0; i < cf_estratto.length(); ++i) {
	        if(i % 2 == 0) dispari = dispari + cf_estratto.charAt(i);
	        else pari = pari + cf_estratto.charAt(i);
	    }
	    int cin = (cinPari(pari) + cinDispari(dispari)) % 26;

	    //si ritorna il carattere corrispondente al CIN calcolato
	    return Character.toString(ALFABETO.charAt(cin));
	}
	
	
	/**
	 * @throws CFexception se codice ha numero di caratteri diverso da 16,
	 * oppure se la disposizione di questi caratteri non e' conforme alla
	 * disposizione: [a-z]{6}[0-9]{2}[a-z][0-9]{2}[a-z][0-9]{3}[a-z]
	 */
	public void controllo() throws CFexception {
		final String CIFRE = ("0123456789");

		//controllo lunghezza codice
		int lunghezza = codice.length();
	    if(lunghezza<16) throw new CFexception ("Codice fiscale troppo corto.");
	    else if(lunghezza>16) throw new CFexception ("Codice fiscale troppo lungo.");
	    	    
		//codice ha 16 caratteri, controllo la disposizione di caratteri e cifre
	    int pos;
	
	    //controllo posizione antroponimo:
	    String tempS = this.estraiCodIdentificativo();
	    int inizio = 0;
	    int fine = tempS.length();
	    for(int it=inizio; it!=fine; ++it) {
	    	char c = tempS.charAt(it); //estrae da temp carattere c in posizione it
	    	pos = ALFABETO.indexOf(c); //se c non e' in ALFABETO, pos assume valore -1
	        if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	    }
	
	    //controllo posizione anno:
	    tempS = this.estraiCodAnno();
	    fine = tempS.length();
	    for(int it=inizio; it!=fine; ++it) {
	    	char c = tempS.charAt(it); //estrae da temp carattere c in posizione it
	        pos = CIFRE.indexOf(c); //se c non e' in CIFRE, pos assume valore -1
	        if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	    }
	
	    //controllo posizione mese:
	    char tempC = this.estraiCodMese();
	    pos = ALFABETO.indexOf(tempC); //se c non e' in ALFABETO, pos assume valore -1
	    if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	    
	    //controllo giorno-sesso
	    tempS = this.estraiCodGiornoSesso();
	    fine = tempS.length();
	    for(int it=inizio; it!=fine; ++it) {
	    	char c = tempS.charAt(it); //estrae da temp carattere c in posizione it
	    	pos = CIFRE.indexOf(c); //se c non e' in CIFRE, pos assume valore -1
	    	if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	    }
	
	    //controllo posizione luogo:
	    tempS = this.estraiCodLuogo();
	    fine = tempS.length();
	    pos = ALFABETO.indexOf(tempS.charAt(0)); //se primo carattere di tempS non e' in alfabeto, pos assume valore -1
	    if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	    for(int it=inizio+1; it!=fine; ++it) {
	    	char c = tempS.charAt(it); //estrae da temp carattere c in posizione it
	        pos = CIFRE.indexOf(c); //se c non e' in CIFRE, pos assume valore -1
	        if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	    }
	
	    //controllo posizione carattere di controllo:
	    tempC = this.estraiCin();
	    pos = ALFABETO.indexOf(tempC);
	    if(pos == -1) throw new CFexception ("Codice fiscale non valido.");
	}

	
	/**
	 * overrides java.lang.Object.toString
	 * @return stringa descrittiva del campo dati di CodiceFiscale
	 */
	public String toString() { return codice; }
}