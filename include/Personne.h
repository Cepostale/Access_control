#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <vector>
using namespace std;

//Classe Personne definit les personnes possedant des badges
class Personne {
private:
    string nom;
    string prenom;
    vector<string> statuts; // Vector pour stocker plusieurs statuts : Enseignant, Eleve, Admnistritatif, Securite, Chercheur
public:
    //Constructeur par defaut
    Personne(): nom(""), prenom("") {}
    //Constructeur par recopie
    Personne(const Personne &p): nom(p.nom), prenom(p.prenom),statuts(p.statuts) {}
    //Operateur affectation
    Personne& operator=(const Personne &p);
    //Destructeur virtuel
    virtual ~Personne() {}

    //Constructeur le plus utilise, tout est renseigne
    Personne(const string &nom, const string &prenom, const string& statut): nom(nom), prenom(prenom) {statuts.push_back(statut);}

    //Getters
    string getNomComplet(){return nom + " " + prenom;}//Getter nom
    //Recupere tous les statuts
    vector<string> getStatuts()const {return statuts;}
    //Recupere le statut principal, virtuelle
    virtual string getStatutPrincipal() const = 0;

    //Verifie si la personne a un statut spécifique
    bool aStatut(const string& statut) const;

    //Ajoute un statut supplementaire
    void ajouterStatut(string statut);

    // Supprimer un statut
    void supprimerStatut(const string& statut);
};

#endif //PERSONNE_H
