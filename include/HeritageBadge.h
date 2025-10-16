#ifndef HERITAGEBADGE_H
#define HERITAGEBADGE_H

#include "Badge.h"
#include "HeritagePersonne.h"

//Definition des differents types de personnes
namespace StatutTypes {
    extern const char Chercheur[];
    extern const char Eleve[];
    extern const char Professeur[];
    extern const char Administratif[];
    extern const char Securite[];
}

//Template pour creer des badges a des personnes specifiques
template<typename UserType, const char* StatutName>
class TypedBadge : public Badge {
public:

    //Constructeur a partir d'un Badge existant
    TypedBadge(const Badge& b) : Badge(b) {}

    //Constructeur a partir d'un utilisateur specifique
    TypedBadge(UserType& utilisateur) : Badge(utilisateur) {}

    //Constructeur complet
    TypedBadge(UserType& utilisateur, bool validite) : Badge(utilisateur, validite) {}

    //Renvoie le statut specifique
    string getStatutUtilisateur() const override {
        return StatutName;
    }
};

#endif //HERITAGEBADGE_H
