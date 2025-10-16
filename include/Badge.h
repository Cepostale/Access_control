#ifndef BADGE_H
#define BADGE_H

#include <iostream>
#include "Personne.h"
using namespace std;

//Classe Badge repertorie tous les badges des personnes par id et nom complet d'utilisaeur + vision de la validite du badge
class Badge {
private:
    static int compteurIdBadge;
    int idBadge;
    Personne& utilisateur;
    bool validite;
public:
    //Constructeur par defaut
    Badge() = delete; //Impossible de creer un badge sans utilisateur
    //Constructeur par recopie
    Badge(const Badge& b): idBadge(compteurIdBadge++), utilisateur(b.utilisateur), validite(b.validite) {};
    //Operateur affectation
    Badge& operator=(const Badge &b);
    //Destructeur
    virtual ~Badge() {};

    //Constructeur, validite non renseigne donc badge desactive
    Badge(Personne& utilisateur):idBadge(compteurIdBadge++),utilisateur(utilisateur), validite(false) {};
    //Constructeur le plus utilise, tout est renseigne
    Badge(Personne& utilisateur, bool validite):idBadge(compteurIdBadge++),utilisateur(utilisateur), validite(validite) {};

    //Permet de savoir si le badge est active
    bool isActif()const;
    //Permet de rendre le badge actif
    void turnValidOn();
    //Permet e rendre le badge inactif
    void turnValidOff();
    //Permet d'obtenir l'id du badge
    int getIdBadge(){return this->idBadge;};

    //Renvoie la personne proprietaire du badge
    Personne& getUtilisateur() const;

    virtual string getStatutUtilisateur() const = 0;
};



#endif //BADGE_H
