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

//Classe Scheduler, initie et joue la simulation complete d'une journee d'ecole
class Scheduler {
private:
    //Vecteur des lecteurs de badges crees
    vector<LecteurBadge*> lecteurs;
    //VEcteurs des badges crees
    vector<Badge*> badges;
    //Cree le serveur
    Serveur serveur;

    //Intervalle entre chaque cycle
    int intervalleSimulation; //millisecondes
    //True si la simulation est en cours, false sinon
    bool simulationEnCours;
    double heureSimulation; //heure fictive pour une journee (0-23) en decimal (7.5=7h30)
    //Heure du debut de la simulation
    double heureDebut; // 7.5 dans notre simulation
    //Heure de fin de la simulation
    double heureFin; //19.0 dans notre simulation
public:
    //Constructeur par defaut, fixation du debut de la journee a 7h30, fin 19h, temps entre chaque cycle 1s, un cycle = 15min dans la simulation.
    Scheduler():intervalleSimulation(1000), simulationEnCours(false), heureSimulation(7.5), heureDebut(7.5), heureFin(19.0), serveur(){} ;
    //Constructeur par recopie
    Scheduler(const Scheduler& sche): serveur(sche.serveur), lecteurs(sche.lecteurs), badges(sche.badges), intervalleSimulation(sche.intervalleSimulation), simulationEnCours(sche.simulationEnCours), heureSimulation(sche.heureSimulation), heureDebut(sche.heureDebut), heureFin(sche.heureFin) {};
    //Operateur affectation
    Scheduler& operator=(const Scheduler& sche);
    //Fin de la simulation
    ~Scheduler();

    //Ajoute les lecteurs crees dans le vecteur lecteurs
    void ajouterLecteurBadge(LecteurBadge* lecteur);
    //Ajoute les badges crees dans le vecteur badges
    void ajouterBadge(Badge* badge);
    //Simule une journee dans l'enceinte du campus
    void simulation();
    //Initialise la simulation
    void initialisation();
    //Arrete la simulation
    void arreterSimulation();
    //Creation d'evenement en fonction des heures de la journee de simulation. Moment de pointe et de creux
    void genererEvenementAleatoire();

    //Incremente le temps de la simulation toutes les deux secondes
    void incrementerHeure();
    //Permet d'afficher l'heure de la simulation pour l'ecrire dans les logs
    string getHeureSimulation() const;
    //True si l'heure de la simulation est entre 7h30 et 19h sinon false
    bool estHeureOuverture() const;

    //Utilise la methode du serveur pour ecrire dans les logs
    void ecrireLog(const string& message, bool isSchedulerLog);
};
#endif //SCHEDULER_H
