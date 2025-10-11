#include "../include/Serveur.h"
#include "../include/LecteurBadge.h"

#include <sstream>      // String streams pour le parsing
#include <stdexcept>    // Exceptions standard
#include <vector>       // Vecteurs dynamiques
#include <fstream>
#include <iomanip>
#include <chrono>


Serveur& Serveur::operator=(const Serveur &s) {
    this->fichierDescription = s.fichierDescription;
    this->fichierLogs = s.fichierLogs;
    this->droitsAcces = s.droitsAcces;
    return *this;
}

ResultatVerification Serveur::verifierTotalAcces(const Badge& badge, const LecteurBadge& lecteur) {
    string statut = badge.getUtilisateur().getStatut();
    string batiment = lecteur.getTypePorte();

    //Verifie si le badge est actif
    if (!badge.isActif()) {
        return {false, "Badge inactif ou invalide"};
    }

    //Verifie si le statut existe
    if (droitsAcces.find(statut) == droitsAcces.end()) {
        return {false, "Statut '" + statut + "' non reconnu dans le systeme"};
    }

    //Verifie si le batiment est configure pour ce statut
    if (droitsAcces[statut].find(batiment) == droitsAcces[statut].end()) {
        return {false, "Acces a '" + batiment + "' non configure pour " + statut};
    }

    //Verifie les droits
    if (!droitsAcces[statut][batiment]) {
        return {false, statut + " n'a pas l'autorisation d'acceder a '" + batiment + "'"};
    }

    //Si tout est bon l'acces est autorise
    return {true, "Acces conforme aux regles de securite"};
}


bool Serveur:: askAcces( Badge& badge, LecteurBadge& lecteur, const string& heureSimulation){
    //Recupere les donnes du badge, personne, lecteurbadge
    const string nomPersonne = badge.getUtilisateur().getNomComplet();
    const string statutPersonne = badge.getUtilisateur().getStatut();
    const string localisationPorte = lecteur.getLocalisation();
    const string typePorte = lecteur.getTypePorte();

    //Verifie les droits
    ResultatVerification resultat = verifierTotalAcces(badge, lecteur);

    //Genere un message de log d'une demande d'acces
    stringstream messageLog;
    messageLog << "DEMANDE_ACCES - Heure: " << heureSimulation
               << " - Personne: " << nomPersonne
               << " | Statut: " << statutPersonne
               << " | Lecteur: " << typePorte
               << " | Localisation: " << localisationPorte
               << " | Resulat: " << (resultat.accesAutorisation ? "AUTORISE" : "REFUSE");

    //Ajout de la raison detaillee si refus
    if (!resultat.accesAutorisation) {
        messageLog << " | Raison: " + resultat.raison;
    }

    //Ecrit dans le fichier log
    saveLogs(messageLog.str(), heureSimulation);

    //Affichage console detaille
    cout << "\n=== DEMANDE D'ACCES ===" << endl;
    cout << "Heure: " << heureSimulation << endl;
    cout << "Personne: " << nomPersonne << endl;
    cout << "Statut: " << statutPersonne << endl;
    cout << "Lecteur: " << typePorte << " - " << localisationPorte << endl;

    if (resultat.accesAutorisation) {
        cout << "ACCES AUTORISE" << endl;
        cout << resultat.raison << endl;
    } else {
        cout << "ACCES REFUSE" << endl;
        cout << resultat.raison << endl;
    }
    cout << "========================" << endl;

    return resultat.accesAutorisation;
}

void Serveur::saveLogs(const string& action, const string& heureSimulation) {
    //Ouverture du fichier en mode ecriture (append) positionne a la fin du fichier
    ofstream fichierLog(fichierLogs, ios::app);

    //Verifie si le fichier s'ouvre
    if (!fichierLog.is_open()) {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de logs: " << fichierLogs << endl;
        return;
    }

    string timestampReel = getTimestampReel();
    fichierLog << "[REEL: " << timestampReel << " SIMU: " << heureSimulation <<"]" << action << endl;

    //Fermeture du fichier log
    fichierLog.close();
}

string Serveur::getTimestampReel() {
    //Recupere l'heure du systeme au moment demande
    chrono::time_point<chrono::system_clock> tempsPresent = chrono::system_clock::now();
    //Traduction du temps C++ en temps C (nombre de secondes depuis 1970)
    time_t timeTValue = chrono::system_clock::to_time_t(tempsPresent);

    stringstream ss;
    //Convertit le temps en heure locale et la formate
    ss << put_time(localtime(&timeTValue),"%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool Serveur:: loadConfiguration(){
    ifstream fichier(fichierDescription);

    //Test 1: Verifie l'ouverture du fichier
    if (!fichier.is_open()) {
        cerr << "ERREUR: Impossible d'ouvrir le fichier '" << fichierDescription << "'" << endl;
        cerr << "Verifiez que le fichier existe et est accessible en lecture." << endl;
        return false;
    }

    //Test 2: Verifie que le fichier n'est pas vide
    if (fichier.peek() == ifstream::traits_type::eof()) {
        cerr << "ERREUR: Le fichier '" << fichierDescription << "' est vide." << endl;
        fichier.close();
        return false;
    }

    string ligne;

    try {
        //Lit la ligne d'en-tete
        if (!getline(fichier, ligne)) {
            throw runtime_error("Impossible de lire la ligne den-tete");
        }

        //Test 3: Verifie que l'en-tête n'est pas vide
        if (ligne.empty()) {
            throw runtime_error("La ligne den-tete est vide");
        }

        vector<string> batiments;
        istringstream ss(ligne);
        string cellule;

        //Lit l'etiquette "Statut" (premiere colonne)
        if (!getline(ss, cellule, ',')) {
            throw runtime_error("Format den-tete invalide - colonne Statut manquante");
        }

        //Test 4: Verifie format en-tête
        if (cellule != "Statut") {
            cerr << "ATTENTION: La premiere colonne devrait s'appeler Statut, mais contient: '"
                 << cellule << "'" << endl;
            // On continue quand même, ce n'est pas fatal
        }

        //Lit noms des batiments
        int nbBatiments = 0;
        while (getline(ss, cellule, ',')) {
            if (cellule.empty()) {
                cerr << "ATTENTION: Nom de batiment vide detecte a la position "
                     << (nbBatiments + 1) << endl;
                cellule = "Batiment_" + to_string(nbBatiments + 1);
            }
            batiments.push_back(cellule);
            nbBatiments++;
        }

        //Test 5: Verifie qu'il y a au moins un batiment
        if (batiments.empty()) {
            throw runtime_error("Aucun batiment defini dans len-tete");
        }

        cout << "Lecture de " << nbBatiments << " batiment(s)..." << endl;

        //Lecture des donnees
        int ligneNum = 1; // Compteur de lignes pour les messages d'erreur
        int statsLus = 0;

        while (getline(fichier, ligne)) {
            ligneNum++;

            //Test 6: Ignore les lignes vides
            if (ligne.empty()) {
                cerr << "ATTENTION: Ligne " << ligneNum << " vide - ignoree" << endl;
                continue;
            }

            istringstream ssLigne(ligne);
            string statut;

            //Lit le statut
            if (!getline(ssLigne, statut, ',')) {
                cerr << "ERREUR: Statut manquant à la ligne " << ligneNum << " - ligne ignoree" << endl;
                continue;
            }

            //Test 7: Verifie que le statut n'est pas vide
            if (statut.empty()) {
                cerr << "ERREUR: Statut vide à la ligne " << ligneNum << " - ligne ignoree" << endl;
                continue;
            }

            //Lit les droits d'acces
            int index = 0;
            string droit;
            int droitsLus = 0;

            while (getline(ssLigne, droit, ',') && index < batiments.size()) {
                //Conversion de la valeur texte en booleen
                bool acces;

                if (droit == "1" || droit == "true" || droit == "oui" || droit == "vrai") {
                    acces = true;
                } else if (droit == "0" || droit == "false" || droit == "non" || droit == "faux" || droit.empty()) {
                    acces = false;
                } else {
                    //Valeur inconnue, on utilise false par defaut et on avertit
                    cerr << "ATTENTION: Valeur inconnue '" << droit << "' pour " << statut
                         << " -> " << batiments[index] << " (defaut: acces refuse)" << endl;
                    acces = false;
                }

                droitsAcces[statut][batiments[index]] = acces;
                index++;
                droitsLus++;
            }

            //Test 8: Verifie le nombre de droits
            if (droitsLus < batiments.size()) {
                cerr << "ATTENTION: Ligne " << ligneNum << " - seulement " << droitsLus
                     << " droit(s) specifie(s) pour " << batiments.size() << " batiment(s)" << endl;
                cerr << "Les droits manquants seront definis à: acces refuse" << endl;

                //Remplit les droits manquants avec false
                for (int i = droitsLus; i < batiments.size(); i++) {
                    droitsAcces[statut][batiments[i]] = false;
                }
            }

            statsLus++;
        }

        //Test 9: Verifie qu'au moins un statut a ete lu
        if (statsLus == 0) {
            throw runtime_error("Aucune donnee de statut trouvee dans le fichier");
        }

        cout << "Succes: " << statsLus << " statut(s) charge(s) avec "
             << nbBatiments << " batiment(s) chacun" << endl;

    } catch (const exception& e) {
        cerr << "ERREUR CRITIQUE lors de la lecture: " << e.what() << endl;
        fichier.close();

        //Nettoie les donnees partiellement chargees
        droitsAcces.clear();
        return false;
    }

    fichier.close();
    return true;
}