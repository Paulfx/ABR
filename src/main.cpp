#include <iostream>

#include "ABR.h"
#include "Element.h"

#include <string>
#include <ctime>

int main(int argc, char** argv) {

	srand(time(NULL));
	
	ABR<Element> test;

	Element e1(25), e2(15), e3(7), e4(64), e5(5), e6(1), e7(25), e8(45);

	/*
	test.recherche(e1);

	test.inserer(e1);
	test.supprimer(e1);
	test.afficherParcoursPrefixe();
	test.inserer(e2);
	test.inserer(e3);
	test.inserer(e4);
	test.inserer(e5);
	test.inserer(e6);
	test.inserer(e7);*/

	for(unsigned int i=0; i<50; ++i) {
		float t = (float) rand()/RAND_MAX;
		e1 = t * 500;
		test.inserer(e1);
	}
	

	test.afficherParcoursPrefixe();
	test.toPng("test.txt");

	
	test.supprimer(e5);
	test.supprimer(e8);
	test.afficherParcoursPrefixe();


	ABR<std::string> test2;

	test2.inserer("salut");

	test2.inserer("aeaea");
	test2.inserer("EHO");
	test2.inserer("blob");
	test2.inserer("pialfp");

	test2.afficherParcoursPrefixe();

	test2.toPng("test2.txt");

	return 0;
}