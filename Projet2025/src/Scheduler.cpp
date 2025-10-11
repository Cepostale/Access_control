#include "../include/Scheduler.h"

#include "../include/Scheduler.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;

Scheduler& Scheduler::operator=(const Scheduler& sche) {
    this->serveur = sche.serveur;
    this->lecteurs = sche.lecteurs;
    this->badges = sche.badges;
    this->intervalleSimulation = sche.intervalleSimulation;
    this->simulationEnCours = sche.simulationEnCours;
    this->heureSimulation = sche.heureSimulation;
    this->heureDebut = sche.heureDebut;
    this->heureFin = sche.heureFin;
    return *this;
}

//Annonce le debut de la journee dans la console
Scheduler :: Scheduler(Serveur& serv, double debut, double fin, int intervalle) : serveur(serv), intervalleSimulation(intervalle), simulationEnCours(false), heureSimulation(debut), heureDebut(debut), heureFin(fin) {
    cout << "Scheduler (ordonnanceur) initialise: " << getHeureSimulation() << " a " << fin << "h (" << (fin - debut)*60 << " minutes)" << endl;
}

Scheduler::~Scheduler() {
    arreterSimulation();
}

void Scheduler::simulation() {
    simulationEnCours = true;
    int cycle = 0;

    cout << "DEBUT DE LA SIMULATION DE LA JOURNEE" << endl;
    ecrireLog("Debut de la simulation", true);
    cout << "Periode: " << getHeureSimulation() << " a " << heureFin << "h" << endl;
    cout << "Duree reelle: " << ((heureFin - heureDebut) * 60 / 2) << " secondes" << endl;

    //Tant que l'heure affiche ne correspond pas a la fin de la journee de la simulation, on augmente de 15 min (1 cycle)
    while (simulationEnCours && heureSimulation < heureFin) {
        cycle++;

        //Affiche dans la console le cycle et l'heure equivalente.
        cout << "\n=== CYCLE " << cycle << " - " << getHeureSimulation() << " ===" << endl;

        //Verifie si c'est l'heure d'ouverture/fermeture
        if (abs(heureSimulation - heureDebut) < 0.01) { //Environ 7h30
            cout << "OUVERTURE DU CAMPUS" << endl;
            ecrireLog("Ouverture du campus - Debut de la journee", true);
        }
        else if (abs(heureSimulation - heureFin) < 0.01) { //Environ 19h00
            cout << "FERMETURE DU CAMPUS" << endl;
            ecrireLog("Fermeture du campus - Fin de la journee", true);
        }

        //Genere des evenements seulement pendant les heures d'ouverture
        if (estHeureOuverture()) {
            genererEvenementAleatoire();
        } else {
            cout << "Campus ferme - Aucun evenement" << endl;
            ecrireLog("Campus ferme - Aucun evenement", false);
        }

        //Attend avant le prochain cycle
        this_thread::sleep_for(chrono::milliseconds(intervalleSimulation));

        //Avance le temps de simulation (15 min par cycle)
        incrementerHeure();
    }

    //Annonce la fin de la journee de simulation si tout s'est bien passe
    if (simulationEnCours) {
        cout << "\nSIMULATION TERMINEE - Fin de la journee a " << getHeureSimulation() << endl;
        ecrireLog("Fin de la simulation - Journee terminee", true);
    }
}

//True si l'heure de la simulation est entre 7h30 et 19h sinon false
bool Scheduler::estHeureOuverture() const {
    return (heureSimulation >= heureDebut && heureSimulation <= heureFin);
}

//Creation d'evenement en fonction des heure de la journee de simulation. Moment de pointe et de creu.
void Scheduler::genererEvenementAleatoire() {
    if (badges.empty() || lecteurs.empty()) {
        cout << "ATTENTION Aucun badge ou lecteur disponible!!!!!!" << endl;
        ecrireLog("Aucun badge ou lecteur disponible", true);
        return;
    }
    //Probabilite variable selon l'heure de la journee
    double probabilite = 0.7; //Normal = 70%

    //Variation de la probabilite d'evenement en fonction de l'heure
    if (heureSimulation >= 8.0 && heureSimulation <= 9.0) { //Matin entre 8h / 9h: heure de pointe forte
        probabilite = 0.9; //90% : pic d'activite
        cout << "HEURE DE POINTE FORTE - Pic d'activite" << endl;
        ecrireLog("HEURE DE POINTE FORTE  - Pic d'activite", false);
    }
    else if ((heureSimulation >= 12.0 && heureSimulation <= 13.0) || //Midi entre 12h / 13h : heure de pointe moderee
        (heureSimulation >= 17.0 && heureSimulation <= 18.0)) { //Soir entre 17h / 18h : heure de pointe moderee
        probabilite = 0.8; //80% : activite elevee
        cout << "HEURE DE POINTE - Activite elevee" << endl;
        ecrireLog("HEURE DE POINTE - Activite elevee", false);
        }
    else if (heureSimulation > 18.0 && heureSimulation <= 19.0) {
        probabilite = 0.3; //30%, tres faible entree
        cout << "ACTIVITE REDUITE" << endl;
        ecrireLog("ACTIVITE REDUITE", false);
    }
    else { //Activite normale (7h30-8h / 9h-12h / 13h-17h), probabilite deja a 70%
        cout << "ACTIVITE NORMALE" << endl;
        ecrireLog("ACTIVITE NORMALE", false);
    }

    //Permet de generer un nombre aleatoire
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disChance(0, 1); //Genere un nombre decimal entre 0 et 1

    if (disChance(gen) > probabilite) { //Si le chiffre genere est superieur a la probabilite d'evenement, rien ne se passe.
        cout << "Aucun événement ce cycle" << endl;
        ecrireLog("Aucun evenement ce cycle", false);
        return;
    }

    //Choisit un badge et un lecteur aléatoires
    uniform_int_distribution<> disBadge(0, badges.size() - 1);
    uniform_int_distribution<> disLecteur(0, lecteurs.size() - 1);

    Badge* badge = badges[disBadge(gen)];
    LecteurBadge* lecteur = lecteurs[disLecteur(gen)];

    cout << "EVENEMENT: " << badge->getUtilisateur().getNomComplet() << " presente son badge sur " << lecteur->getLocalisation() << endl;

    //Demande l'autorisation via le lecteur
    bool autorise = lecteur->askAutorisation(*badge, getHeureSimulation());
    if (autorise) {
        lecteur->openPorte();
    }
}

//Incremente le temps de la simulation toutes les deux secondes
void Scheduler::incrementerHeure() {
    heureSimulation += 0.25; //15 minutes par cycle

    //Verifie si on a depasse l'heure de fin
    if (heureSimulation >= heureFin) {
        simulationEnCours = false;
    }
}

//Permet d'afficher l'heure de la simulation pour l'ecrire dans les logs
string Scheduler::getHeureSimulation() const {
    int heures = static_cast<int>(heureSimulation); //Enleve la partie decimale de l'heure de la simulation
    int minutes = static_cast<int>((heureSimulation - heures) * 60); //Recupere la partie decimale de l'heure de la simulation

    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", heures, minutes); //Ecrit l'heure dans la forme HH:MM
    return string(buffer);
}

//Utilise la methode du serveur pour ecrire dans les logs
void Scheduler::ecrireLog(const string& message, bool isSchedulerLog = true) {

    stringstream logMessage;

    if (isSchedulerLog) {
        logMessage << "SCHEDULER - " << message;
    } else {
        logMessage << message;
    }
    serveur.saveLogs(logMessage.str(), getHeureSimulation());
}

void Scheduler::ajouterLecteurBadge(LecteurBadge* lecteur) {
    lecteurs.push_back(lecteur); //Permet d'ajouter un lecteur en fin de liste (vector)
    cout << "Lecteur ajoute: " << lecteur->getLocalisation() << endl;
}

void Scheduler::ajouterBadge(Badge* badge) {
    badges.push_back(badge); //Permet d'ajouter un badge en fin de liste (vector)
    cout << "Badge ajoute: " << badge->getUtilisateur().getNomComplet() << endl;
}

//Arrete la simulation
void Scheduler::arreterSimulation() {
    simulationEnCours = false;
}