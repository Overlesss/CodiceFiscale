package codicefiscalePkg;


/** 
 * La classe base astratta DatiPersona dichiara
 * i metodi virtuali puri che vengono implementati
 * da tutte le sue sottoclassi.  
 * */
public abstract class DatiPersona {

    public abstract void creaDaCodice(final String s) throws CFexception;
    public abstract String generaCodice();
    public abstract void controllo() throws CFexception;
    public abstract String toString();
}
