#include "Element.h"

Element::Element(const unsigned int id) { _id = id; }

Element::Element(const Element& e) { _id = e._id; }

bool Element::operator ==(const Element& e){
	return _id == e._id;
}

bool Element::operator <=(const Element& e){
	return _id <= e._id;
}

bool Element::operator >=(const Element& e){
	return _id >= e._id;
}

bool Element::operator <(const Element& e){
	return _id < e._id;
}

bool Element::operator >(const Element& e){
	return _id > e._id;
}

std::ostream& operator <<(std::ostream& os, const Element& e) {
	os << e._id;
	return os;
}