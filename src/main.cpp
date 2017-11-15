#include <iostream>

#include "ABR.h"
#include "Element.h"

#include <string>

int main(int argc, char** argv) {
	
	ABR<Element> test;

	Element e1(25), e2(15), e3(7), e4(64), e5(5), e6(1), e7(25), e8(45);

	test.recherche(e1);

	test.inserer(e1);
	test.supprimer(e1);
	test.afficherParcoursPrefixe();
	test.inserer(e2);
	test.inserer(e3);
	test.inserer(e4);
	test.inserer(e5);
	test.inserer(e6);
	test.inserer(e7);

	test.afficherParcoursPrefixe();

if(test.recherche(e5)) std::cout<<"On l'a !!"<<std::endl;
	
	test.supprimer(e5);
	test.supprimer(e8);
	test.afficherParcoursPrefixe();

	if(test.recherche(e5)) std::cout<<"On l'a !!"<<std::endl;

	ABR<std::string> test2;

	test2.inserer("salut");

	test2.inserer("aeaea");

	test2.afficherParcoursPrefixe();

	return 0;
}