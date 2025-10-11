#ifndef SERVEUR_H
#define SERVEUR_H

#include "Badge.h"
#include <iostream>
#include <string>
#include <map>          // Maps (dictionnaires)

class LecteurBadge;

//Centralise le resulat de chaque verificiation d'acces : retourne le resulat et la raison si refus
struct ResultatVerification {
    bool accesAutorisation;
    string raison;

    //Constructeur pour faciliter la creation
    ResultatVerification(bool acces, const string& raisonMsg = "") : accesAutorisation(acces), raison(raisonMsg) {}
};

//Decrire la classe Serveur
class Serveur {
private:
    string fichierDescription;
    string fichierLogs;
    //Map de maps : organise donnees sur 3 niveaux : statut de la personne, batiment, droit d'acces
    map<string, map<string, bool>> droitsAcces;

    //Effectue toutes les verifications necessaires pour determiner l'acces
    ResultatVerification verifierTotalAcces(const Badge& badge, const LecteurBadge& lecteur);
    //Genre un timestamp reel. Format: YYYY-MM-DD HH:MM:SS
    string getTimestampReel();
public:
    //Constructeur par defaut
    Serveur() = delete;//Interdiction d'instancier un serveur sans les fichiers
    //Constructeur par recopie
    Serveur(const Serveur &s): fichierDescription(s.fichierDescription), fichierLogs(s.fichierLogs), droitsAcces(s.droitsAcces) {};
    //Operateur affectation
    Serveur& operator=(const Serveur &s);
    //Destructeur
    ~Serveur() {};


    Serveur(const string& fichierDescription, const string& fichierLogs) : fichierDescription(fichierDescription), fichierLogs(fichierLogs) {}

    bool askAcces( Badge& badge, LecteurBadge& lecteur, const string& heureSimulation);

    bool loadConfiguration();

    void saveLogs(const string& action, const string& heureSimulation = "");;
};



#endif //SERVEUR_H
