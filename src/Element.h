#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <iostream>

class Element {

private:

	unsigned int _id;

public:

	Element(const unsigned int id);
	Element(const Element& e);

	bool operator ==(const Element& e);
	bool operator <=(const Element& e);
	bool operator >=(const Element& e);
	bool operator <(const Element& e);
	bool operator >(const Element& e);

	friend std::ostream& operator <<(std::ostream& os, const Element& elem);
};

#endif //_ELEMENT_H