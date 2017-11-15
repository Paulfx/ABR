#ifndef _NOEUD_H
#define _NOEUD_H

#include "ABR.h"

template <class Type> class ABR;

template <class Type>
class Noeud {
	friend class ABR<Type>;

private:

    Type* _elem ;
    Noeud* _fg;
    Noeud* _fd;
    bool vide;

public:

	Noeud();

	Noeud(const Type& elem, Noeud<Type>* fg = 0, Noeud<Type>* fd = 0);

	~Noeud();

	Type& element();

	const Type& element() const;

	void element(const Type& elem);

	void copie(const Noeud<Type>& node);
};

#endif //_NOEUD_H