#include "ABR.h"
#include "Element.h"
#include <iostream>

template <class Type>
ABR<Type>::ABR() {
	nbElem = 0;
	adRacine = 0;
}

template <class Type>
ABR<Type>::ABR(const ABR<Type>& abr) {
	nbElem = abr.nbElem; 
	adRacine = new Noeud<Type>(abr.adRacine->element());
	adRacine->copie(*abr.adRacine);
}

template <class Type>
ABR<Type>::~ABR() { delete adRacine; }

template <class Type>
void ABR<Type>::inserer(const Type& e) {
	//infoFils& test = noFils;*
	int a = 0;
	inserer(adRacine, e, a);
}

template <class Type>
void ABR<Type>::supprimer(const Type& e) {
	if(!adRacine->vide) supprimer(adRacine, e, adRacine);
}

template <class Type>
bool ABR<Type>::recherche(const Type& e) const {
	return recherche(adRacine, e);
}

template <class Type>
void ABR<Type>::afficherParcoursPrefixe() const {
	std::cout<<"Affichage pré-fixé : ";
	affichePrefixeRecursive(adRacine);
	std::cout<<std::endl;
}

template <class Type>
void ABR<Type>::afficherParcoursInfixe() const {
	afficheInfixeRecursive(adRacine);
}

template <class Type>
void ABR<Type>::afficherParcoursPostfixe() const {
	affichePostfixeRecursive(adRacine);
}

/**
 * Private
 */


template <class Type>
bool ABR<Type>::recherche(Noeud<Type>* node, const Type& e) const {
	if (node == 0) return false;
	else if (node->element() == e) return true;
	else if (node->element() > e) return recherche(node->_fg, e);
	else return recherche(node->_fd, e);
}

template <class Type>
void ABR<Type>::inserer(Noeud<Type>*& node, const Type& e, int& info) {
	if (node == 0) node = new Noeud<Type>(e);
	else if (node->element() > e) {
		inserer(node->_fg, e, info);
		//Traitement remontée gauche
		info = 1;
	}
	else if (node->element() < e) {
		inserer(node->_fd, e, info);
		//Traitement remontée droite
		info = 2;
	}
	std::cout<<"VALEUR DE INFO : "<<info<<std::endl;
}

template <class Type>
void ABR<Type>::supprimer(Noeud<Type>* node, const Type& e, Noeud<Type>* ancienNoeud) {
	if (node != 0) {
		if (node->element() > e) supprimer(node->_fg, e, node);
		else if (node->element() < e) supprimer(node->_fd, e, node);
		else if (node->_fg == 0) supprimerElement(node, ancienNoeud);
		else if (node->_fd == 0) supprimerElement(node, ancienNoeud);
		else { //2 fils
			Type max = chercheMaxGauche(node->_fg, node);
			node->element(max);
		}
	} 
}

template <class Type>
void ABR<Type>::supprimerElement(Noeud<Type>* node,  Noeud<Type>* ancienNoeud) {
	if(ancienNoeud == node) { //On supprime la tête de l'arbre
		ancienNoeud = node->_fd;
	}
	else {
		if(ancienNoeud->_fd == node) ancienNoeud->_fd = node->_fd;
		else ancienNoeud->_fg = node->_fd;
		delete node;
	}
}

//Cherche et supprime
template <class Type>
Type ABR<Type>::chercheMaxGauche(Noeud<Type>* node,  Noeud<Type>* ancienNoeud) {
	if (node->_fd == 0) {
		Type elem = *(node->_elem);
		delete node;
		if (ancienNoeud->_fd == node) ancienNoeud->_fd = 0;
		else ancienNoeud->_fg = 0;
		return elem;
	}
	else return chercheMaxGauche(node->_fd, node);
}

template <class Type>
void ABR<Type>::affichePrefixeRecursive(const Noeud<Type>* node) const {
	
	if (node != 0) {
		std::cout<<*(node->_elem)<<", ";
		affichePrefixeRecursive(node->_fg);
		affichePrefixeRecursive(node->_fd);
	}
}

template <class Type>
void ABR<Type>::afficheInfixeRecursive(const Noeud<Type>* node) const {
	if(node != 0) {
		afficheInfixeRecursive(node->_fg);
		std::cout<<*(node->_elem)<<", ";
		afficheInfixeRecursive(node->_fd);
	}
}

template <class Type>
void ABR<Type>::affichePostfixeRecursive(const Noeud<Type>* node) const {
	if(node != 0) {
		affichePostfixeRecursive(node->_fg);
		affichePostfixeRecursive(node->_fd);
		std::cout<<*(node->_elem)<<", ";
	}
}

//Declaration des types "prévus", nécessaires si l'on veut utiliser un header file 
//ET un fichier .cpp

template class ABR<Element>;
template class ABR<int>;
template class ABR<std::string>;