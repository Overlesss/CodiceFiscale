package codicefiscalePkg;


/**
 * La classe Identificativo rappresenta l'antroponimo
 * di una Persona, ed il sesso come sottooggetto.
 * Contiene funzioni utili per il controllo e
 * il calcolo del codice fiscale e del suo inverso.
 */
public class Identificativo extends Sesso {
	private String nome;
	private String cognome;
	
    private static final String VOCALI = ("AEIOU");

	
	public Identificativo() { this("",""); }

	
	public Identificativo(String n, String c) {
		super();
		nome = n;
		cognome = c;
	}


	//costruttore di copia
	public Identificativo(final Identificativo a) {
		super(a);
	    nome = a.nome;
	    cognome = a.cognome;
	}

	
	/**
	 * @return numero consonanti trovate in
	 * @param str
	 */
	private static int contaConsonanti(String str) {
		//str contiene vocali e consonanti
	    int conta_consonanti = 0;
	    for(int it = 0; it < str.length(); ++it) {
	    	char c = str.charAt(it); //estrazione carattere c da str in posizione it
	    	//ricerca c in VOCALI
	    	if(VOCALI.indexOf(c) == -1)
	    		//c non trovato in VOCALI => c e' consonante
	    		conta_consonanti +=1;
	    }
	    return conta_consonanti;
	}
	

	/**
	 * @return stringa di 3 caratteri che rappresentano
	 * cognome nel codice fiscale
	 */
	private String generaCodCognome() {
		//codice cognome sara' composto dalle consonanti, se presenti, seguite dalle vocali, nel loro ordine
		//cognome contiene almeno 2 caratteri
		
		String cod = ""; //conterra' codice cognome
		char c1, c2;
		
		//cognome contiene 2 caratteri, si aggiunge X alla fine
	    if(cognome.length() < 3) {
	    	c1 = cognome.charAt(0);
    		c2 = cognome.charAt(1);
    		if(VOCALI.indexOf(c1) != -1)
    			//il primo carattere di cognome e' una vocale
    			if(VOCALI.indexOf(c2) == -1)
    				//il secondo carattere di cognome e' una vocale
    				return c2 + c1 + "X"; //ritorna consonante + vocale + X
    		return cognome + "X"; //negli altri casi, ritorna cognome + X
	    }
	    
	    //cognome ha almeno 3 caratteri, si estraggono consonanti nel loro ordine
	    int it = 0;
	    while(it<cognome.length() && cod.length()<3) {
	    	c1 = cognome.charAt(it);
	    	if(VOCALI.indexOf(c1) == -1)
	    		//c1 e' una consonante
	    		cod = cod + c1;
	    	++it;
	    }
	    //se cod ha meno di 3 caratteri, si aggiungono le vocali di cognome nel loro ordine
	    if(cod.length() < 3) {
	    	it = 0;
	    	while(cod.length()!=3) {
	    		c1 = cognome.charAt(it);
	    		if(VOCALI.indexOf(c1) != -1)
	    			//c1 e' una vocale
	    			cod = cod + c1;
	    		++it;
	    	}
	    }
	    return cod; //cod e' composto da 3 caratteri
	}
	
	
	/**
	 * @return stringa di 3 caratteri che rappresentano
	 * nome nel codice fiscale
	 */
	private String generaCodNome() {
    	//codice nome sara' composto dalle consonanti, se presenti, seguite dalle vocali, nel loro ordine
		//nome contiene almeno 2 caratteri
		
		String cod = ""; //conterra' codice nome
		char c1, c2;
		
		//nome contiene 2 caratteri, si aggiunge X alla fine
	    if(nome.length() < 3) {
	    	c1 = nome.charAt(0);
    		c2 = nome.charAt(1);
    		if(VOCALI.indexOf(c1) != -1)
    			//il primo carattere di nome e' una vocale
    			if(VOCALI.indexOf(c2) == -1)
    				//il secondo carattere di nome e' una vocale
    				return c2 + c1 + "X"; //ritorna consonante + vocale + X
    		return nome + "X"; //negli altri casi, ritorna nome + X
	    }
	    
	    //nome ha almeno 3 caratteri, si estraggono consonanti nel loro ordine
        int n_cons = contaConsonanti(nome);
        int it = 0, conta = 0;
    	while(it<nome.length() && cod.length() < 3) {
        	c1 = nome.charAt(it);
    	    if(VOCALI.indexOf(c1) == -1 ) {
    	    	//c1 e' una consonante
    	    	if(n_cons >3) {
    	    		//n_cons > 3 => si prendono la 1a, 3a e 4a consonante del nome
	    	    	conta += 1;
	    	    	if(conta != 2)
	    	    		cod = cod + c1;
	    	    } else 
	    	    	//n_cons <= 3, si prendono le consonanti nell'ordine in cui si trovano
	    	    	cod = cod + c1;
    	    }
    	    ++it;
    	}

    	//se cod ha meno di 3 caratteri (quindi anche meno di 2 consonanti), si aggiungono le vocali di cognome nel loro ordine
	    if(cod.length() < 3) {
	    	it = 0;
	    	while(cod.length()!=3) {
	    		c1 = cognome.charAt(it);
	    		if(VOCALI.indexOf(c1) != -1)
	    			//c1 e' una vocale
	    			cod = cod + c1;
	    		++it;
	    	}
	    }
	    return cod; //cod e' composto da 3 caratteri
    }
    
    
	/** @return stringa del campo dati cognome. */
    public String estraiCognome() { return cognome; }
	
	
    /**
     * @param cod contiene 6 caratteri del codice fiscale
     * identificano nome e cognome.
     * I primi 3 caratteri vengono assegnati a cognome, gli ultimi 3 a nome.
     */
	public void creaDaCodice(final String cod) throws CFexception {
	    cognome = cod.substring(0,3);
	    nome = cod.substring(3, cod.length()-1);
	}
	
	
	/**
	 * @return stringa di 6 caratteri per il codice fiscale
	 * che rappresenta cognome e nome.
	 */
	public String generaCodice() {
	    return generaCodCognome() + generaCodNome();
	}
	

	/**
	 * @throws CFexception se nome o cognome hanno meno di 3 caratteri,
	 * oppure se nome o cognome contengono caratteri non in ALFABETO.
	 */
	public void controllo() throws CFexception {

	    //controllo lunghezza antroponimo
	    if(nome.length() < 2 || cognome.length() < 2) throw new CFexception("Nome o cognome troppo corti.");

	    //controllo caratteri antroponimo (nome e cognome non contengono spazi)
	    final String ALFABETO = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	    for(int it = 0; it < nome.length(); ++it) {
	    	char c = nome.charAt(it); //estrazione carattere c da nome in posizione it
	    	if(ALFABETO.indexOf(c) == -1) throw new CFexception("Nome non valido."); //controllo che c sia in ALFABETO
	    }
	    for(int it = 0; it != cognome.length(); ++it) {
	    	char c = cognome.charAt(it); //estrazione carattere c da cognome in posizione it
	    	if(ALFABETO.indexOf(c) == -1) throw new CFexception("Cogome non valido."); //controllo che c sia in ALFABETO
	    }
	}
	

	/**
	 * overrides java.lang.Object.toString
	 * @return stringa descrittiva dei campi dati di Identificativo
	 */
	public String toString() {
	    return (cognome + " " + nome);
	}
	
}
