#ifndef BADGE_H
#define BADGE_H

#include <iostream>
#include "Personne.h"
using namespace std;

//Classe Badge repertorie tous les badges des personnes par id et nom complet d'utilisaeur + vision de la validite du badge
class Badge {
private:
    int idBadge;
    Personne& utilisateur;
    bool validite;
public:
    //Constructeur par defaut
    Badge() = delete; //Impossible de creer un badge sans utilisateur
    //Constructeur par recopie
    Badge(const Badge& b): idBadge(b.idBadge), utilisateur(b.utilisateur), validite(b.validite) {};
    //Operateur affectation
    Badge& operator=(const Badge &b);
    //Destructeur
    ~Badge() {};

    //Constructeur le plus utilise, tout est renseigne
    Badge(int idBadge, Personne& utilisateur):idBadge(idBadge),utilisateur(utilisateur), validite(false) {};

    //Permet de savoir si le badge est active
    bool isActif()const;
    //Permet de rendre le badge actif
    void turnValidOn();
    //Permet e rendre le badge inactif
    void turnValidOff();

    //Renvoie la personne proprietaire du badge
    Personne& getUtilisateur() const;
};



#endif //BADGE_H
