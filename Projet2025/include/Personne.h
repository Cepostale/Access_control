#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
using namespace std;

//Classe Personne definit les personnes possedant des badges
class Personne {
private:
    string nom;
    string prenom;
    string statut; //Enseignant, Eleve, Admnistritatif, Securite, Chercheur
public:
    //Constructeur par defaut
    Personne(): nom(""), prenom(""), statut("") {}
    //Constructeur par recopie
    Personne(const Personne &p): nom(p.nom), prenom(p.prenom),statut(p.statut) {}
    //Operateur affectation
    Personne& operator=(const Personne &p);
    //Destructeur
    ~Personne() {}

    //Constructeur le plus utilise, tout est renseigne
    Personne(string nom, string prenom, string statut): nom(nom), prenom(prenom), statut(statut) {}

    //Getters
    string getNomComplet(){return nom + " " + prenom;}//Getter nom
    string getStatut(){return statut;} //Getter statut
};

#endif //PERSONNE_H
