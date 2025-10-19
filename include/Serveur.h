#ifndef SERVEUR_H
#define SERVEUR_H

#include "Badge.h"
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

//Gere les acces des differents statuts, mise a jour des logs dans un fichier log
class Serveur {
private:
    //Fichier possedant les droits de chaque statut de personne
    string fichierDescription;
    //Fichier avec les logs en detail selon la journee de la simulation
    string fichierLogs;
    //Map de maps : organise donnees sur 3 niveaux : statut de la personne, batiment, droit d'acces
    map<string, map<string, bool>> droitsAcces;

    //Effectue toutes les verifications necessaires pour determiner l'acces
    ResultatVerification verifierTotalAcces(const Badge& badge, const LecteurBadge& lecteur);
    //Genere un timestamp reel. Format: YYYY-MM-DD HH:MM:SS
    string getTimestampReel();
public:
    //Constructeur par defaut
    Serveur(): fichierDescription(""), fichierLogs("") {};
    //Constructeur par recopie
    Serveur(const Serveur &s): fichierDescription(s.fichierDescription), fichierLogs(s.fichierLogs), droitsAcces(s.droitsAcces) {};
    //Operateur affectation
    Serveur& operator=(const Serveur &s);
    //Destructeur
    ~Serveur() {};

    //Constructeur, parametre: fichier des acces selon les statuts et le fichier de log a remplir
    Serveur(const string& fichierDescription, const string& fichierLogs) : fichierDescription(fichierDescription), fichierLogs(fichierLogs) {}

    //Renvoie le resultat de la demande d'acces s'un badge sur un lecteur. Rempli la console et le fichier log avec les details de la demande
    bool askAcces( Badge& badge, LecteurBadge& lecteur, const string& heureSimulation);

    //Remplit accesDroit en fonction des droits inscrits dans le fichierDescription
    bool loadConfiguration();

    //Enregistre les logs (avec le prenom, le lieu, l'heure, et le resulat de la demande) dasn le fichier 'fichierLogs'
    void saveLogs(const string& action, const string& heureSimulation = "");

    //Getter de la taille des statuts d'une personne, permet d'apprendre a utiliser l'amitie
    int tailleStatut(const Personne& pers) {return pers.statuts.size();};
};



#endif //SERVEUR_H
