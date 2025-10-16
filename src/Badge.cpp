#include "../include/Badge.h"
using namespace std;

int Badge::compteurIdBadge = 1;

Badge &Badge::operator=(const Badge &b) {
    this->validite = b.validite;
    //L'id n'est pas modifie on garde celui de base
    //la reference est unique ne peut pas prendre d'autres valeur
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
