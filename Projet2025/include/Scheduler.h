#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <random>
#include "Serveur.h"
#include "LecteurBadge.h"
#include "Badge.h"
#include "Personne.h"

using namespace std;

class Scheduler {
private:
    vector<LecteurBadge*> lecteurs;
    vector<Badge*> badges;
    Serveur& serveur;
    int intervalleSimulation; //millisecondes
    bool simulationEnCours;
    double heureSimulation; //heure fictive pour une journee (0-23) en decimal (7.5=7h30)
    double heureDebut; // 7.5 dans notre simulation
    double heureFin; //19.0 dans notre simulation
public:
    //Constructeur par defaut impossible car serveur doit être initialisé
    Scheduler() = delete ;
    //Constructeur par recopie
    Scheduler(const Scheduler& sche): serveur(sche.serveur), lecteurs(sche.lecteurs), badges(sche.badges), intervalleSimulation(sche.intervalleSimulation), simulationEnCours(sche.simulationEnCours), heureSimulation(sche.heureSimulation), heureDebut(sche.heureDebut), heureFin(sche.heureFin) {};
    //Operateur affectation
    Scheduler& operator=(const Scheduler& sche);
    //Fin de la simulation
    ~Scheduler();

    //Fixation du debut de la journee a 7h30, fin 19h, temps entre chaque cycle 1s, un cycle = 15min dans la simulation.
    Scheduler(Serveur& serv, double debut = 7.5, double fin = 19.0, int intervalle = 1000);

    //Ajoute les lecteurs crees dans le vecteur lecteurs
    void ajouterLecteurBadge(LecteurBadge* lecteur);
    //Ajoute les badges crees dans le vecteur badges
    void ajouterBadge(Badge* badge);
    //Simule une journee dans l'enceinte du campus
    void simulation();
    //Initialise la simulation
    void initialisation(Serveur& serv);
    //Arrete la simulation
    void arreterSimulation();
    //Creation d'evenement en fonction des heure de la journee de simulation. Moment de pointe et de creux
    void genererEvenementAleatoire();

    //Incremente le temps de la simulation toutes les deux secondes
    void incrementerHeure();
    //Permet d'afficher l'heure de la simulation pour l'ecrire dans les logs
    string getHeureSimulation() const;
    //True si l'heure de la simulation est entre 7h30 et 19h sinon false
    bool estHeureOuverture() const;
    //double getHeure() const {return heureSimulation;}

    //Utilise la methode du serveur pour ecrire dans les logs
    void ecrireLog(const string& message, bool isSchedulerLog);
};
#endif //SCHEDULER_H
