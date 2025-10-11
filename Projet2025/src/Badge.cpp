#include "../include/Badge.h"
using namespace std;

Badge &Badge::operator=(const Badge &b) {
    this->utilisateur = b.utilisateur;
    this->idBadge = b.idBadge;
    this->validite = b.validite;
    return *this;
}

bool Badge::isActif()const{
  return validite;
}

void Badge::turnValidOn(){
  validite = true;
}

void Badge::turnValidOff(){
    validite = false;
}

Personne& Badge::getUtilisateur() const {
    return utilisateur;
}
