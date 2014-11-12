
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.semanticweb.HermiT.Reasoner;
import org.semanticweb.owlapi.apibinding.OWLManager;
import org.semanticweb.owlapi.io.OWLXMLOntologyFormat;
import org.semanticweb.owlapi.model.IRI;
import org.semanticweb.owlapi.model.OWLAxiom;
import org.semanticweb.owlapi.model.OWLDataFactory;
import org.semanticweb.owlapi.model.OWLOntology;
import org.semanticweb.owlapi.model.OWLOntologyManager;

import com.sun.xml.internal.ws.util.StringUtils;

public class ClasseTP2 {
	
	static OWLOntologyManager manager;
	static OWLOntology ont1, ont2;	
	
	public static void main(String[] args) throws Exception {
		
		System.out.println("Bonjour");
		
		maFonction();
		
		maDeuxiemeFonction();
		}
	
	public static void maFonction() throws Exception {	
		manager = OWLManager.createOWLOntologyManager();
		
		File inputOntologyFile1 = new File("TP_2/TP2/TP2/GRO.xml");
		ont1 = manager.loadOntologyFromOntologyDocument(inputOntologyFile1);
		
		IRI doc = IRI.create("file:/home/matthias/Dropbox/dev/work/ia_resolution_contraintes/TP_2/TP2/TP2//validGCIs.xml");
		ont2 = manager.createOntology();
		manager.saveOntology(ont2, new OWLXMLOntologyFormat(), doc);
		
	}
	
	public static void maDeuxiemeFonction() throws Exception
	{
		OWLDataFactory dataFactory = manager.getOWLDataFactory();
		Reasoner reasoner = new Reasoner(ont1);
		
		//File gcis = new File("TP_2/TP2/TP2/gcis");
		Scanner scanner=new Scanner(new File("TP_2/TP2/TP2/gcis"));
		IRI doc = IRI.create("file:/home/matthias/Dropbox/dev/work/ia_resolution_contraintes/TP_2/TP2/TP2//validGCIs.txt");
		
		while (scanner.hasNextLine()) {
			System.out.println("------------------------------------------------");
		    String line = scanner.nextLine();
		    /* (gci (and ExperimentalMethod_cncpt Protein_cncpt) ⊥) */

		    
		    getAxiomFromLine(line);
		    /*
		    Pattern pattern = Pattern.compile("\\p{Space}([A-Za-z]*)_cncpt");  
		    Matcher matcher = pattern.matcher(line);
		    String cpt = new String();		    
		    while(matcher.find())
		    {
		    	cpt = matcher.group(1);
		    	System.out.println(cpt);		    	
		    }*/
		    
		    
		    
		    //System.out.println(matcher.groupCount());
		    /*ExperimentalMethod_cncpt ET Protein_cncpt*/
		    /*
		    
		    OWLAxiom axiom = null;
		    if(reasoner.isEntailed(axiom)isSatisfiable)
			{
				// Dans le fichier validGCIs.txt
				// Dans le fichier validGCIs.xml
			}*/
		}
	
		
		/*
		 * OWLAxiom axiom = ...
		 * 
		 */
		
		// gcis parcourir
		//gcis.
		
		//OWLAxiom axiom = dataFactory.getOWLSubClassOfAxiom()
		//OWLAxiom axiom=dataFactory.getOWLSubClassOfAxiom(margherita, hasToppingMozarellaOrGoatsCheese);
				
		//if(reasoner.isEntailed(axiom))
		//{
			// Dans le fichier validGCIs.txt
			// Dans le fichier validGCIs.xml
		//}
		
		
	}
	
	public static String EvalChaine(String s)
	{
		if(s.length() != 0){
			/*
			System.out.println(s);
			String toto = s.substring(0,s.indexOf(")"));
			System.out.println(toto);
			String tyty = toto.substring(toto.lastIndexOf("(")+1);
			System.out.println(tyty);
			*/
			
			int thomas = s.lastIndexOf(")");
			if(thomas != -1){
				String toto = s.substring(0,thomas);
				int yannig = toto.indexOf("(");
				String tyty = new String();
				if(yannig != -1){
					tyty = toto.substring(yannig+1);
					System.out.println(tyty);
				}
				else{
					tyty = "";
				}
			
	
				EvalChaine(tyty);
				
			}
		}
		
		
		return s;
		
	}
	
	public static String getAxiomFromLine(String line)
	{
		
		return EvalChaine(line);
		
	}

}
