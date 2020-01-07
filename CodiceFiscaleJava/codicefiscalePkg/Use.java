package codicefiscalePkg;

/** 
 * La classe Use implementa un'applicazione che permette
 * il calcolo del codice fiscale dai dati di una persona presi in input,
 * il controllo di validita' di un codice fiscale inserito,
 * oppure l'estrazione dei dati di nascita e del sesso da un codice fiscale inserito.
 * */
public class Use {
	
	public static void sceltaFunzione (int fun, boolean continua) {
		try {
		    System.out.println("Scegliere un'operazione:");
		    System.out.println("(1) Calcolo codice fiscale,");
		    System.out.println("(2) Verifica validita' codice fiscale,");
		    System.out.println("(3) Estrazione dati codice fiscale,");
		    System.out.println("(0) Per uscire dal programma.");
		    System.out.print("Prego digitare il numero della funzione desiderata: ");
		    System.out.println(fun);

		    //scelta funzione
		    int pos;
		    String cifre_fun = "0123";
	    
		    char f = (Integer.toString(fun)).charAt(0);
		    
		    //controllo validita' input
		    pos=cifre_fun.indexOf(f);

		    if(pos == -1) throw new CFexception("Input non corretto");
		    if(pos == 0) continua=false;
		}
		catch(CFexception me) { System.err.println(me.estraiErrore()); sceltaFunzione(fun,continua); } //input non corretto, richiesta se continuare o terminare
	}
	

	/** @param fun identifica funzione da eseguire. */
	public static void eseguiFunzione(final int fun) {
	    //fun contiene: 1-calcolo cf, 2-verifica validita' cf, 3-estrazione dati cf
	    switch(fun) {

	        //calcolo cf
	        case 1: {
            	Soggetto s = new Soggetto();
	            Identificativo nominativo = new Identificativo();
	            Sesso sex = new Sesso();
	            Nascita datiNascita = new Nascita();
	            try {
	            	String cognome, nome, stato_nascita, luogoNascita, comune, provincia;
	        		Data dataNascita;

	                System.out.println("\nDigitare caratteri senza accenti.");

	                //costruzione antroponimo (possibili input contenenti spazi):
	                System.out.print("Inserisci cognome: ");
	                cognome = "Rossi";
	                System.out.println(cognome);
	                cognome = cognome.replaceAll("\\s+",""); //eliminazione spazi
	                cognome = cognome.toUpperCase(); //trasforma caratteri minuscoli in maiuscoli
	                System.out.print("Inserisci nome: ");	                
	                nome = "Gian Marco"; 
	                System.out.println(nome);
	                nome = nome.replaceAll("\\s+",""); //eliminazione spazi
	                nome = nome.toUpperCase(); //trasforma caratteri minuscoli in maiuscoli
	                
	                try { 
	                	nominativo = new Identificativo(nome, cognome);
	                	nominativo.controllo();
	                }
	                catch(CFexception me) { System.err.println("Errore. " + me.estraiErrore()); throw new CFexception("Funzione terminata."); }
	                s.assegna(nominativo);

	                //costruzione sesso
	                System.out.print("Inserire sesso (m/f): ");
	                char c = 'm';
	                System.out.println(c);
	                c = Character.toUpperCase(c);
	                try {
	                	sex = new Sesso(c);
	                	sex.controllo();
	                } catch(CFexception me) { System.err.println("Errore. " + me.estraiErrore()); throw new CFexception("Funzione terminata."); }
	                s.assegna(sex);

	                //costruzione data:
	        		System.out.print("Inserire data di nascita (nel formato: gg-mm-aa): ");
	        		int g=1, m=1 ,a=01;
	        		try {
	        			dataNascita = new Data(a,m,g);
	        			System.out.println(g + "/" + m + "/" + a);
	        			dataNascita.controllo();
	        		} catch(CFexception me) { System.err.println("Errore. " + me.estraiErrore()); throw new CFexception("Funzione terminata."); }

	                //costruzione luogo (possibili input con spazi):
	        		System.out.print("Inserire stato di nascita: ");
	        		stato_nascita = "Italia";
	                System.out.println(stato_nascita);
	                stato_nascita = stato_nascita.toUpperCase();
	                if(stato_nascita.equals("ITALIA")) {
	                	System.out.print("Inserire comune di nascita: ");
	                    comune = "Firenze";
	                    System.out.println(comune);
	                    comune = comune.toUpperCase();
	                    System.out.print("Inserire sigla provincia: ");
	                    provincia = "fi";
	                    System.out.println(provincia);
	                    provincia = provincia.toUpperCase();
	                    luogoNascita = comune + " (" + provincia + ")";
	                } else luogoNascita = stato_nascita;

	                try {
	                	datiNascita = new Nascita(dataNascita, luogoNascita);
	                	//controllo esistenza luogo ed estrazione codice belfiore corrispondente
	                	datiNascita.controllo();
	                } catch(CFexception me) { System.err.println("Errore. " + me.estraiErrore()); throw new CFexception("Funzione terminata."); }
	        		s.assegna(datiNascita);
	            	
	            	CodiceFiscale cfGenerato = new CodiceFiscale();
	            	String cod = Soggetto.generaCodice(nominativo) + Soggetto.generaCodice(datiNascita);
	            	
	        	    //se persona di sesso femminile, a codice giorno va sommato 40
	        	    String codS = Soggetto.generaCodice(sex);
	        	    if(codS != "0") {
	        	        int codG = datiNascita.estraiGiorno();
	        	        codG += Integer.parseInt(codS);
	        	        
	        	        cod = cod.substring(0, 9) + codG + cod.substring(11);
	        	    }
	        	    CodiceFiscale cfTemp = new CodiceFiscale(cod); //cfTemp composto da 15 caratteri
	        	    cod = cod.concat(Soggetto.generaCodice(cfTemp));
	        	    cfGenerato.creaDaCodice(cod);
	        	    s.assegna(cfGenerato);	            	
	            	System.out.println("\nIl codice fiscale e': " + cfGenerato + '\n');
	            } catch(Exception me) { System.err.println(me.getMessage()); }
	            break;
	        }
	        //2: verifica validita' - 3: verifica validita' + estrazione dati
	        case 2: case 3: {
	            try {
	                Nascita datiNascita = new Nascita();
	                Sesso sesso = new Sesso();
	                
	                //in input codice fiscale, controllo lunghezza e corretta posizione caratteri/cifre
	                System.out.print("\nInserire il codice fiscale: ");
	                String c = "rssgmr01a01d612c"; 
	                System.out.println(c);
	                c = c.toUpperCase();
	                CodiceFiscale cf = new CodiceFiscale(c);
	                cf.controllo();
	                
	                Soggetto anonimo = new Soggetto(cf);
	                
	                String codNascita = cf.estraiCodAnno() + cf.estraiCodMese() + cf.estraiCodGiornoSesso() + cf.estraiCodLuogo();
	        	    datiNascita = (Nascita) anonimo.creaDaCodice(datiNascita,codNascita);
	        	
	        	    String codGiornoSesso = cf.estraiCodGiornoSesso();
	        	    sesso = (Sesso) anonimo.creaDaCodice(sesso,codGiornoSesso);
	                
	                //calcolo cin atteso da cf in input
	                //controllo corrispondenza cin atteso a cin estratto da cf, se non corrisponde cf e' non valido
	                final String cin_atteso = Soggetto.generaCodice(cf);
	                cf.controlloCin(cin_atteso);
	                if(fun == 2)
	                    //fun==2, si richiede solo verifica del codice fiscale
	                    System.out.println("\nCodice fiscale valido.");
	                else
	                    //fun==3, si richiede stampa dei dati estratti dal codice fiscale
	                	System.out.println("\nDati soggetto estratti da" + anonimo);
	            }
	            catch(CFexception me) { System.err.println(me.estraiErrore()); }
	            break;
	        }
	    }
	}

	
	public static void nuovaOperazione(boolean continua) {
		try {
		    //scelta se continuare o terminare
			System.out.print("Eseguire una nuova operazione? S/N: ");
		    char n;
	
		    //controllo validita' input
		    int pos;
		    String scelta_ok = "SsNn";
		    n = 's'; System.out.println(n);
		    pos=scelta_ok.indexOf(n);
		    if(pos == -1) throw new CFexception("Input non corretto.");
		    if(pos==2 || pos==3) continua=false;
		}
		catch(CFexception me) { System.err.println(me.estraiErrore()); nuovaOperazione(continua); } //input non corretto, rilanciata funzione nuovaOperazione

	}	
	
	
	public static void main (String args[]) {
		int fun=1;
	    boolean continua=true;

        //scelta funzione da eseguire
        sceltaFunzione(fun,continua);
        if(continua) {

            //esecuzione funzione
            eseguiFunzione(fun);

            //richiesta se continuare o terminare
            nuovaOperazione(continua);
            
            fun = 3;
            sceltaFunzione(fun,continua);

          //esecuzione funzione
            eseguiFunzione(fun);

            continua = false;
        }
	    System.out.println("Programma terminato.\n");
	}

}
