package codicefiscalePkg;


/**
 * La classe Data rappresenta la data di nascita
 * di una Persona. Contiene funzioni utili per il controllo e
 * il calcolo del codice fiscale e del suo inverso.
 */
public class Data extends DatiPersona {
	private int anno;
    private int mese;
    private int giorno;
    
    private static final String CODICI_MESI = ("ABCDEHLMPRST");
 

    public Data() {
    	this(0,0,0);
    }
        
       
    public Data(int a, int m, int g) {
    	anno = a;
    	mese = m;
    	giorno = g;
    }
        
    
    //costruttore di copia
    public Data(final Data d) {
    	anno = d.anno;
    	mese = d.mese;
    	giorno = d.giorno;
    }

    
    /** @return valore del campo dati giorno. */
    public int estraiGiorno() { return giorno; }
    
    
    /**
     * @param cod contiene sottostringa del codice fiscale relativa alla data di nascita.
     * Creati campi dati anno, mese, giorno dalla sottostringa.
     * @throws CFexception se carattere mese non compare in CODICI_MESI.
     */
    public void creaDaCodice (final String cod) throws CFexception {
	
	    //creazione anno
	    anno = Integer.parseInt(cod.substring(0,2));
	
	    //creazione mese
	    int m = 0;
	    boolean trovato = false;
	  //cerca corrispondenza di c con caratteri in CODICI_MESI
        for(int it = 0; !trovato && it < CODICI_MESI.length(); ++it) {
            m += 1;
            if(CODICI_MESI.charAt(it) == cod.charAt(2)) trovato = true;
        }
	    //se trovato, il codice mese estratto dal codice fiscale e' valido
        if(trovato) mese = m;
        else throw new CFexception("Codice mese errato.");
	
	    //creazione giorno
	    giorno = Integer.parseInt(cod.substring(3,cod.length()));
	    if(giorno>31) giorno -= 40;
	}
	
	
    /**
     * @return stringa di 5 caratteri creata da anno, mese, giorno
     * che rappresenta parte di codice fiscale relativa a data di nascita.
     */
	public String generaCodice() {
	    String cod = "";
	
	    //generazione codice anno
	    //se untime due cifre anno <9, si concatena uno zero
	    if(anno <= 9) cod = "0" +  anno;
	    else cod += anno;
	
	    //generazionne codice corrispondente a mese
	    cod += CODICI_MESI.charAt(mese-1);
	
	    //generazione codice giorno
	    //se giorno <9, si concatena uno zero
	    if(giorno <= 9) cod = cod + "0" + giorno;
	    else cod = cod + giorno;
	
	    return cod;
	}
	
	
	/** @throws CFexception se oggetto Data non rappresenta data esistente. */
    public void controllo() throws CFexception {
        final int[] MAX_GIORNI_MESI = {31,29,31,30,31,30,31,31,30,31,30,31};
    	if((mese < 1 || mese > 12) || (giorno < 1 || giorno > 31)) throw new CFexception("Data non corretta."); //anno e' composto da 2 cifre e puo' assumere tutti i valori tra 0 e 99
        int g_max = MAX_GIORNI_MESI[mese-1];
        //giorno non deve essere maggiore del massimo dei giorni per il mese estratto
        if(g_max < giorno) throw new CFexception("Data non corretta.");
        if(mese == 2 && giorno > 28) { //controllo giorni anni bisestili
            if(!(((anno%4 == 0)&&(anno%100 != 0)) || (anno%400 == 0))) throw new CFexception("Data non corretta.");
        }
    }
	
	
	/**
	 * overrides java.lang.Object.toString
	 * @return stringa descrittiva dei campi dati di Data
	 */
	public String toString() {
		String g = Integer.toString(giorno);
    	String m = Integer.toString(mese);
    	String a = Integer.toString(anno);
	    if(giorno < 10) g = "0" + g;
	    if(mese < 10) m = "0" + m;
	    if(anno < 10) a = "0" + a;
	    String dataS = g + "/" + m + "/" + "19" + a;
	    //i nati tra 1900-1918 hanno le stesse 2 cifre relative all'anno dei nati tra 2000-2018
	    if(anno < 18) dataS += " oppure " + g + "/" + m + "/" + "20" + a;
	    return dataS;
	}
}
