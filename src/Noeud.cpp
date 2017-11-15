#include "Noeud.h"
#include "Element.h"

template <class Type>
Noeud<Type>::Noeud() {
	_elem = 0;
	_fg = 0;
	_fd = 0;
	vide = true;
}

template <class Type>
Noeud<Type>::Noeud(const Type& elem, Noeud<Type>* fg, Noeud<Type>* fd) {
	_elem = new Type(elem);
	vide = false;
	_fg = fg;
	_fd = fd;
}	

template <class Type>
Noeud<Type>::~Noeud() {
	delete _elem;
	delete _fg;
	delete _fd;
}

template <class Type>
Type& Noeud<Type>::element() { return *_elem;}

template <class Type>
const Type& Noeud<Type>::element() const { return *_elem;}

template <class Type>
void Noeud<Type>::element(const Type& elem) { 
	if (vide) {
		_elem = new Type(elem);
		vide = false;
	}
	else *_elem = elem; 
}


template <class Type>
void Noeud<Type>::copie(const Noeud<Type>& node) {
	if (node._fg != 0) {
		Noeud<Type>* fg = new Noeud<Type>(*node._elem);
		fg->copie(*node._fg);
	}
	if (node._fd != 0) {
		Noeud<Type>* fd = new Noeud<Type>(*node._elem);
		fd->copie(*node._fd);
	}
}



template class Noeud<Element>;
template class Noeud<int>;
template class Noeud<std::string>;