package org.coode.owlapi.examples;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Iterator;
import java.util.Set;

import org.semanticweb.HermiT.Reasoner;
import org.semanticweb.owlapi.apibinding.OWLManager;
import org.semanticweb.owlapi.model.IRI;
import org.semanticweb.owlapi.model.OWLClass;
import org.semanticweb.owlapi.model.OWLClassExpression;
import org.semanticweb.owlapi.model.OWLDataFactory;
import org.semanticweb.owlapi.model.OWLObjectProperty;
import org.semanticweb.owlapi.model.OWLOntology;
import org.semanticweb.owlapi.model.OWLOntologyCreationException;
import org.semanticweb.owlapi.model.OWLOntologyManager;
import org.semanticweb.owlapi.reasoner.NodeSet;
import org.semanticweb.owlapi.io.*;

public class Example1bis {
	
	public static void main(String[] args) throws Exception {
		
		getSignature();
		getSuperClassOf();
		
	}
	public static void getSignature() throws Exception {
		
        // A simple example of how to load and save an ontology
        // We first need to obtain a copy of an OWLOntologyManager, which, as the
        // name suggests, manages a set of ontologies.  An ontology is unique within
        // an ontology manager.  Each ontology knows its ontology manager.
        // To load multiple copies of an ontology, multiple managers would have to be used.		
      
		OWLOntologyManager manager = OWLManager.createOWLOntologyManager();
        
		// We load an ontology from a file 
		
		File inputOntologyFile = new File("examples/ontologies/GRO.xml");
		OWLOntology ontology = manager.loadOntologyFromOntologyDocument(inputOntologyFile);
		
		// Print out all of the classes which are contained in the signature of the ontology.
        // These are the classes that are referenced by axioms in the ontology.
		
		String cname = "";
		
		for(OWLClass cls : ontology.getClassesInSignature())
		{
			System.out.println(cls);
			cname = cls.toStringID();
			cname = cname.substring(26,cname.length());
			 
		}
		
		for(OWLObjectProperty p : ontology.getObjectPropertiesInSignature())
		{
			System.out.println(p);
		}
		
	}
	
	public static Set<OWLClass> getSuperClassOf() throws OWLOntologyCreationException {
		
		OWLOntologyManager manager = OWLManager.createOWLOntologyManager();		
		File inputOntologyFile = new File("examples/ontologies/GRO.xml");
		System.out.println("Loading the ontology");
		OWLOntology ontology = manager.loadOntologyFromOntologyDocument(inputOntologyFile);
		OWLDataFactory factory = manager.getOWLDataFactory();
		System.out.println("Ontology is loaded");
		OWLClass A = factory.getOWLClass(IRI.create("http://www.bootstrep.eu/ontology/GRO#DosageCompensation"));
		OWLClass B = factory.getOWLClass(IRI.create("http://www.bootstrep.eu/ontology/GRO#ResponseToDrug"));
		
        OWLClassExpression union = factory.getOWLObjectUnionOf(A,B);
        
        Reasoner reasoner=new Reasoner(ontology);       
        
        System.out.println("Starting to get super classes of the given concepts");
        NodeSet<OWLClass> supClses = reasoner.getSuperClasses(union, false);
        System.out.println("The super classes are obtained");
		
        Set<OWLClass> flatsupcls = supClses.getFlattened();
        Iterator<OWLClass> it = flatsupcls.iterator();
 
        while (it.hasNext()){
            System.out.println("A superclass of the given set of concepts is    " + it.next().toString());            
        }
        
		return flatsupcls;		
	}
}
