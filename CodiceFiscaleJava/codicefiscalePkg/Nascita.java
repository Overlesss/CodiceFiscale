package codicefiscalePkg;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;


/**
 * La classe Nascita rappresenta il luogo di nascita
 * di una Persona, e la data di nascita come sottooggetto.
 * Contiene funzioni utili per il controllo e
 * il calcolo del codice fiscale e del suo inverso.
 */
public class Nascita extends Data {
	private String luogo;
	private String belfiore;
	
	
	public Nascita() { this(""); }


	public Nascita(String b) { super(); luogo = ""; belfiore = b; }
	

	public Nascita(Data d, String l) {
		super(d);
		luogo = l;
		belfiore = "";
	}

	
	//costruttore di copia
	public Nascita(final Nascita n) {
		super(n);
		luogo = n.luogo;
	 	belfiore = n.belfiore;
	 }

	
	/*
	 * Apre e legge righe del file in
	 * @param list_luoghi
	 */
	private static void apriFile(List<Nascita> list_luoghi) throws FileNotFoundException {

		/**
		 * file contenente nell'ordine (campi separati da tabulazioni):
		 * codice belfiore,
		 * luogo: Stato per estero, Comune (sigla provincia) per italia;
		 */
		Scanner x = new Scanner (new File("belfiore.txt"));
		while(x.hasNextLine()) {
			String[] campo = (x.nextLine().split("\t"));
			Nascita temp = new Nascita();
			temp.belfiore = campo[0];
			temp.luogo = campo[1];
			list_luoghi.add(temp);
		}
		x.close();		
	}
		
	
	/** @return stringa del campo dati luogo */
	public String estraiLuogo() { return luogo; }
		
	
	/**
	 * @param cod contiene sottostringa di 9 caratteri usati
	 * per creare Data e luogo di Nascita. 
	 */
	public void creaDaCodice (final String cod) throws CFexception {
		super.creaDaCodice(cod.substring(0,5));
	    super.controllo();
	    belfiore = cod.substring(5);
	    
	    /** controllo assegna campo dati luogo, se trovata corrispondenza */
	    controllo();
	}
	

	/** @return stringa del campo dati belfiore */
	public String generaCodice() {
	    //in controllo che segue input dei dati, viene assegnato campo belfiore, se trovata corrispondenza
	    return belfiore;
	}

	
	/** 
	 * Se controllo per luogo, assegno capo dati belfiore associato in list_luoghi;
	 * @throws CFexception se luogo non viene trovato.
	 * Se controllo per belfiore, assegno capo dati luogo associato in list_luoghi;
	 * @throws CFexception se belfiore non viene trovato. 
	 * */
	public void controllo() throws CFexception {
	    List<Nascita> list_luoghi = new ArrayList<Nascita>();

	    //apertura file belfiore.txt ed estrazione dati in vec_luoghi
	    try { apriFile(list_luoghi); } 
	    catch(FileNotFoundException fnfe) { System.err.println("File belfiore.txt non trovato. Programma terminato."); System.exit(0); }
	    catch(Exception e) { e.printStackTrace(); }
	    
	    //ricerca campo dati luogo in vec_luoghi
	    boolean trovato = false;

	    if(luogo.equals("") == false) {
		    for(Nascita n : list_luoghi)
		        //se si trova corrispondenza, si estrae codice belfiore corrispondente
			    	if((n.luogo).equals(luogo)) {
			    		belfiore = n.belfiore;
			    		trovato = true;
			    		break;
			    	}
	    } else {
	    	for(Nascita n : list_luoghi)
		        //se si trova corrispondenza, si estrae luogo corrispondente
			    	if((n.belfiore).equals(belfiore)) {
			    		luogo = n.luogo;
			    		trovato = true;
			    		break;
			    	}
	    }
	    //se campo dati luogo non trovato, non si puo' continuare con la generazione del codice fiscale
	    if(!trovato) {
	    	if(luogo.equals("") == false) throw new CFexception("Luogo non trovato.");
	    	else throw new CFexception("Codice belfiore non corretto.");
	    }
	}


	/**
	 * overrides java.lang.Object.toString
	 * @return stringa descrittiva dei campi dati e sottooggetti di Nascita
	 */
	public String toString() {
	    String nascitaS = " data di nascita: " + super.toString() + "\n";
	    nascitaS += " luogo di nascita: " + luogo;
	    return nascitaS;
	}

}
