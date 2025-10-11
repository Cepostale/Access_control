#include "../include/Personne.h"

Personne& Personne::operator=(const Personne &p) {
    this->nom = p.nom;
    this->prenom = p.prenom;
    this->statut = p.statut;
    return *this;
}