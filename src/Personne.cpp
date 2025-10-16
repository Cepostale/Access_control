#include "../include/Personne.h"

Personne& Personne::operator=(const Personne &p) {
    if (this != &p) {
        this->nom = p.nom;
        this->prenom = p.prenom;
        this->statuts = p.statuts;
    }
    return *this;
}

bool Personne::aStatut(const string& statut) const {
    for (const string& s : statuts) {
        if (s == statut) return true;
    }
    return false;
}

void Personne::ajouterStatut(string statut) {
    if (!statut.empty()) {
        if (!aStatut(statut)) {
            this->statuts.push_back(statut);
        }
    }
}

void Personne::supprimerStatut(const string& statut) {
    //Verifie que le statut existe
    for (vector<string>::iterator it = this->statuts.begin(); it != this->statuts.end(); it++) {
        if (*it == statut) {
            this->statuts.erase(it);
        }
    }
}