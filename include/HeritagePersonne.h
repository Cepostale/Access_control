#ifndef HERITAGEPERSONNE_H
#define HERITAGEPERSONNE_H

#include "Personne.h"
using namespace std;

//Classe Eleve, heritage public de la classe Personne
class Eleve : public Personne {
public:

    //Constructeur, assigne automatiquement le statut Eleve
    Eleve(const string &nom, const string &prenom):Personne(nom, prenom, "Eleve"){};

    //Constructeur avec ajout de statuts supplementaires
    Eleve (const string& nom, const string& prenom, const vector<string>& statuts_supp):Personne(nom,prenom,"Eleve") {
        for (const string& statut : statuts_supp) {
            ajouterStatut(statut);
        }
    }

    //Renvoie le statut principal Eleve
    string getStatutPrincipal()const override {return "Eleve";};

};

//Classe Professeur, heritage public de la classe Personne
class Professeur : public Personne {
public:

    //Constructeur, assigne automatiquement le statut Professeur
    Professeur(const string& nom, const string& prenom):Personne(nom, prenom, "Professeur"){};

    //Constructeur avec ajout de statuts supplementaires
    Professeur (const string& nom, const string& prenom, const vector<string>& statuts_supp):Personne(nom,prenom,"Professeur") {
        for (const string& statut : statuts_supp) {
            ajouterStatut(statut);
        }
    }

    //Renvoie le statut principal Professeur
    string getStatutPrincipal()const override {return "Professeur";};
};

//Classe Chercheur, heritage public de la classe Personne
class Chercheur : public Personne {
public:

    //Constructeur, assigne automatiquement le statut Chercheur
    Chercheur(const string& nom, const string& prenom):Personne(nom, prenom, "Chercheur"){};

    //Constructeur avec ajout de statuts supplementaires
    Chercheur (const string& nom, const string& prenom, const vector<string>& statuts_supp):Personne(nom,prenom,"Chercheur") {
        for (const string& statut : statuts_supp) {
            ajouterStatut(statut);
        }
    }

    //Renvoie le statut principal Chercheur
    string getStatutPrincipal()const override {return "Chercheur";};
};

//Classe Admin, heritage public de la classe Personne
class Admin : public Personne {
public:

    //Constructeur, assigne automatiquement le statut Administration
    Admin(const string& nom, const string& prenom):Personne(nom, prenom, "Administration"){};

    //Constructeur avec ajout de statuts supplementaires
    Admin (const string& nom, const string& prenom, const vector<string>& statuts_supp):Personne(nom,prenom,"Administration") {
        for (const string& statut : statuts_supp) {
            ajouterStatut(statut);
        }
    }

    //Renvoie le statut principal Administration
    string getStatutPrincipal()const override {return "Administration";};
};

//Classe Securite, heritage public de la classe Personne
class Securite : public Personne {
public:

    //Constructeur, assigne automatiquement le statut Securite
    Securite(const string& nom, const string& prenom):Personne(nom, prenom, "Securite"){};

    //Constructeur avec ajout de statuts supplementaires
    Securite(const string& nom, const string& prenom, const vector<string>& statuts_supp):Personne(nom,prenom,"Securite") {
        for (const string& statut : statuts_supp) {
            ajouterStatut(statut);
        }
    }

    //Renvoie le statut principal Securite
    string getStatutPrincipal()const override {return "Securite";};
};

#endif //HERITAGEPERSONNE_H
