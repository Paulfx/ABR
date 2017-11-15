#ifndef _ABR_H
#define _ABR_H

#include "Noeud.h"


template <class Type> class ABR;
template <class Type> class Noeud;

template <class Type>
class ABR {

private:

    Noeud<Type>* adRacine;
    unsigned int nbElem;

    bool recherche(Noeud<Type>* node, const Type& e) const;
    void inserer(Noeud<Type>* node, const Type& e);
    void affichePrefixeRecursive(const Noeud<Type>* node) const;

    void supprimer(Noeud<Type>* node, const Type& e, Noeud<Type>* ancienNoeud);
    void supprimerElement(Noeud<Type>* node, Noeud<Type>* ancienNoeud);
    Type chercheMaxGauche(Noeud<Type>* node, Noeud<Type>* ancienNoeud);
public:

    ABR();
    /* Postcondition : l'ABR est initialement vide */

    ABR(const ABR<Type>& a);

    ~ABR();

    void supprimer(const Type& e);

    void inserer(const Type& e);
    /* Postcondition : si e n'existe pas déjà dans l'ABR, alors un nouveau noeud contenant e est inséré,
                       si e existe déjà dans l'ABR, alors l'ABR est inchangé */

    bool recherche(const Type& e) const;
    /* Postcondition : Si aucun noeud de l'ABR ne contient la valeur e, trouve vaut faux.
                       Si on a trouvé un noeud avec le e demandé, alors trouve vaut vrai.
                       Dans les deux cas, nb_visites contient le nombre de noeuds testés lors de cette recherche. */

    //Affichage

    void afficherParcoursInfixe() const;
    void afficherParcoursPrefixe() const;
    void afficherParcoursPostfixe() const;


};

#endif //_ABR_H