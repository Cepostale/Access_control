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
    //Regarde parmi tous les statuts de la personne si elle possede le statut demande
    for (const string& s : statuts) {
        if (s == statut) return true;
    }
    return false;
}

void Personne::ajouterStatut(string statut) {
    //Verifie si le statut que l'on ajoute n'est pas ''
    if (!statut.empty()) {
        //Verifie si le statut n'est pas deja affecte a la personne
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