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
	std::cout<<'.'<<std::endl;
}

template <class Type>
void ABR<Type>::afficherParcoursInfixe() const {
	std::cout<<"Affichage infixe : ";
	afficheInfixeRecursive(adRacine);
	std::cout<<'.'<<std::endl;
}

template <class Type>
void ABR<Type>::afficherParcoursPostfixe() const {
	std::cout<<"Affichage post-fixé : ";
	affichePostfixeRecursive(adRacine);
	std::cout<<'.'<<std::endl;
}

template <class Type>
bool ABR<Type>::toPng(const char* filename) const {
	std::ofstream f(filename);
	if (!f.is_open()) return false;
	f << "digraph ABR {\n\n\tnode [fontname=\"Arial\", shape=circle, style=filled, color=black, fontcolor=white]\n";
	if(adRacine == 0) f << "\n";
	else if (adRacine->_fg == 0 && adRacine->_fd == 0) f << "\t" << adRacine->element() << "\n";
	else toPng(adRacine, f);
	f <<"\n}";
	f.close();
	return true;
}

template <class Type>
void ABR<Type>::toPng(Noeud<Type>* node, std::ofstream& f) const {
	static unsigned int nbNull = 0;
	if (node->_fg != 0) {
		if (node->_fg->_rouge) f<<"\t"<<node->_fg->element()<<" [color=red]\n";
		f <<"\t"<<node->element()<<" -> "<<node->_fg->element()<<"\n";
		toPng(node->_fg, f);
	}
	else toPngNull(node->element(), f, nbNull++);
	if (node->_fd != 0) {
		if (node->_fd->_rouge) f<<"\t"<<node->_fd->element()<<" [color=red]\n";
		f <<"\t"<<node->element()<<" -> "<<node->_fd->element()<<"\n";
		toPng(node->_fd, f);
	}
	else toPngNull(node->element(), f, nbNull++);
}

template <class Type>
void ABR<Type>::toPngNull(const Type& e, std::ofstream& f, unsigned int nbNull) const {
	f <<"\tnull"<<nbNull<<" [shape=point]\n";
	f <<"\t"<<e<<" -> null"<<nbNull<<"\n";
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
void ABR<Type>::inserer(Noeud<Type>*& node, const Type& e, infoPetitFils& info) {
	if (node == 0) {
		node = new Noeud<Type>(e);
		if (node == adRacine) node->_rouge = false;
	}
	else if (node->element() > e) {
		inserer(node->_fg, e, noPetitFils);
		//Traitement remontée gauche

		if (info == 1 && node->_fg->_rouge && node->_fg->_fg->_rouge) { //node->_fg->_fg != 0
			if (node->_fd != 0 && node->_fd->_rouge) { //Un oncle rouge
				if (node != adRacine) node->_rouge = true;
				node->_fg->_rouge = false;
				node->_fd->_rouge = false;
			}
			else rotationDroite(node);
		}
		else if (info == 2 && node->_fg->_rouge && node->_fg->_fd->_rouge) { //node->_fg->_fd != 0
			if (node->_fd != 0 && node->_fd->_rouge) { //Un oncle rouge
				if (node != adRacine) node->_rouge = true;
				node->_fg->_rouge = false;
				node->_fd->_rouge = false;
			}
			else rotationDoubleDroite(node);
		}

		info = 1;
		
	}
	else if (node->element() < e) {
		inserer(node->_fd, e, noPetitFils);
		//Traitement remontée droite

		bool gauche = false;

		if (info == 1 && node->_fd->_rouge && node->_fd->_fg->_rouge) { //node->_fd->_fg != 0
			if (node->_fg != 0 && node->_fg->_rouge) { //Un oncle rouge
				if (node != adRacine) node->_rouge = true;
				node->_fg->_rouge = false;
				node->_fd->_rouge = false;
			}
			else rotationDoubleGauche(node);
		}
		else if (info == 2 && node->_fd->_rouge && node->_fd->_fd->_rouge) { //node->_fd->_fd != 0
			if (node->_fg != 0 && node->_fg->_rouge) { //Un oncle rouge
				if (node != adRacine) node->_rouge = true;
				node->_fg->_rouge = false;
				node->_fd->_rouge = false;
			}
			else rotationGauche(node);
		}

		info = 2;
	}
}

template <class Type>
void ABR<Type>::inserer(Noeud<Type>*& node, const Type& e, bool& modifHauteur) {
	if (node == 0) 
}

//node->_fg->_fg != 0
template <class Type>
void ABR<Type>::rotationDroite(Noeud<Type>*& node) {
	Noeud<Type>* pere = node;
	node = node->_fg;
	pere->_fg = node->_fd;
	node->_fd = pere;
	//Couleurs 
	pere->_rouge = true;
	node->_rouge = false;

	/*
	//Diff
	node->_diff = 0;
	node->_fd->_diff = 0;*/
}

//node->_fd->_fd != 0
template <class Type>
void ABR<Type>::rotationGauche(Noeud<Type>*& node) {
	Noeud<Type>* pere = node;
	node = node->_fd;
	pere->_fd = node->_fg;
	node->_fg = pere;
	//Couleurs
	pere->_rouge = true;
	node->_rouge = false;
}

//node->_fg->_fd != 0
template <class Type>
void ABR<Type>::rotationDoubleDroite(Noeud<Type>*& node) {
	Noeud<Type>* pere = node;
	node = node->_fg->_fd;

	pere->_fg->_fd = node->_fg;
	node->_fg = pere->_fg;

	pere->_fg = node->_fd;
	node->_fd = pere;
	//Couleurs
	pere->_rouge = true;
	node->_rouge = false;

}

//node->_fd->_fg != 0
template <class Type>
void ABR<Type>::rotationDoubleGauche(Noeud<Type>*& node) {
	Noeud<Type>* pere = node;
	node = node->_fd->_fg;

	pere->_fd->_fg = node->_fd;
	node->_fd = pere->_fd;

	pere->_fd = node->_fg;
	node->_fg = pere;
	//Couleurs
	pere->_rouge = true;
	node->_rouge = false;

	//rotationGauche(node);
	//rotationGauche(node);
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
		if (node != adRacine) std::cout<<", ";
		std::cout<<*(node->_elem);
		affichePrefixeRecursive(node->_fg);
		affichePrefixeRecursive(node->_fd);
	}
}

template <class Type>
void ABR<Type>::afficheInfixeRecursive(const Noeud<Type>* node) const {
	if(node != 0) {
		if (node != adRacine) std::cout<<", ";
		afficheInfixeRecursive(node->_fg);
		std::cout<<*(node->_elem);
		afficheInfixeRecursive(node->_fd);
	}
}

template <class Type>
void ABR<Type>::affichePostfixeRecursive(const Noeud<Type>* node) const {
	if(node != 0) {
		if (node != adRacine) std::cout<<", ";
		affichePostfixeRecursive(node->_fg);
		affichePostfixeRecursive(node->_fd);
		std::cout<<*(node->_elem);
	}
}

//Declaration des types "prévus", nécessaires si l'on veut utiliser un header file 
//ET un fichier .cpp

template class ABR<Element>;
template class ABR<int>;
template class ABR<std::string>;