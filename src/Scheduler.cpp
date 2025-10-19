#include "../include/Scheduler.h"
#include "../include/HeritagePersonne.h"
#include "../include/HeritageBadge.h"
#include "../include/HeritageLecteur.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;

Scheduler& Scheduler::operator=(const Scheduler& sche) {
    this->lecteurs = sche.lecteurs;
    this->badges = sche.badges;
    this->intervalleSimulation = sche.intervalleSimulation;
    this->simulationEnCours = sche.simulationEnCours;
    this->heureSimulation = sche.heureSimulation;
    this->heureDebut = sche.heureDebut;
    this->heureFin = sche.heureFin;
    return *this;
}

Scheduler::~Scheduler() {
    arreterSimulation();
}

void Scheduler::initialisation() {
    cout << "DEMARRAGE DU SYSTEME DE SECURITE" << endl;
    cout << "===================================" << endl;

    //1. Creation du serveur
    serveur = Serveur("../DescriptionFile.csv", "../LogFile.log" );
    //Chargement de la configuration
    serveur.loadConfiguration();

    //2. Creation des personnes
    cout << "\nCREATION DES PERSONNES..." << endl;
    
    //Eleve
    Eleve lila = Eleve("Bois", "Lila");
    Eleve pierre = Eleve("Caillou", "Pierre");
    pierre.ajouterStatut("Professeur");
    Eleve martin = Eleve("Rio", "Martin");
    Eleve marie = Eleve("Poule", "Marie");
    Eleve valerie = Eleve("Didio", "Valerie");

    //Securite
    Securite hugo = Securite("Fevri", "Hugo");
    Securite flavie = Securite("Tichon", "Flavie");

    //Professeur
    Professeur marc = Professeur("Blanc", "Marc");
    marc.ajouterStatut("Chercheur");
    Professeur lison = Professeur("Porte", "Lison");
    Professeur alexis = Professeur("Henri", "Alexis");

    //Administration
    Admin jean = Admin("Jean", "Jean");
    Admin sylvie = Admin("Petit", "Sylvie");

    cout << "12 personnes creees" << endl;

    //3. Creation des badges
    // Activation de certains badges (simulation de badges valides/invalides)
    cout << "\nCREATION DES BADGES..." << endl;
    //Badge Eleve
    TypeBadge<Eleve, StatutTypes::Eleve> lilaBadge = TypeBadge<Eleve, StatutTypes::Eleve>(lila, true);
    TypeBadge<Eleve, StatutTypes::Eleve> pierreBadge = TypeBadge<Eleve, StatutTypes::Eleve>(pierre, true);
    TypeBadge<Eleve, StatutTypes::Eleve> martinBadge = TypeBadge<Eleve, StatutTypes::Eleve>(martin); //Invalide
    TypeBadge<Eleve, StatutTypes::Eleve> marieBadge = TypeBadge<Eleve, StatutTypes::Eleve>(marie, true);
    TypeBadge<Eleve, StatutTypes::Eleve> valerieBadge = TypeBadge<Eleve, StatutTypes::Eleve>(valerie, true);

    //Badge Securite
    TypeBadge<Securite, StatutTypes::Securite> hugoBadge = TypeBadge<Securite, StatutTypes::Securite>(hugo,true);
    TypeBadge<Securite, StatutTypes::Securite> flavieBadge = TypeBadge<Securite, StatutTypes::Securite>(flavie,true);
    
    //Badge Professeur
    TypeBadge<Professeur, StatutTypes::Professeur> marcBadge = TypeBadge<Professeur, StatutTypes::Professeur>(marc, true);
    TypeBadge<Professeur, StatutTypes::Professeur> lisonBadge = TypeBadge<Professeur, StatutTypes::Professeur>(lison, true);
    TypeBadge<Professeur, StatutTypes::Professeur> alexisBadge = TypeBadge<Professeur, StatutTypes::Professeur>(alexis, true);

    //Administration
    TypeBadge<Admin, StatutTypes::Administratif> jeanBadge = TypeBadge<Admin, StatutTypes::Administratif>(jean, true);
    TypeBadge<Admin, StatutTypes::Administratif> sylvieBadge = TypeBadge<Admin, StatutTypes::Administratif>(sylvie, true);
    
    cout << "12 badges crees (1 inactif)" << endl;

    //4. Creation des lecteurs
    cout << "\nINSTALLATION DES LECTEURS..." << endl;
    //Batiment
    LectBadgeBat lecteurBatimentA = LectBadgeBat("Batiment A - Porte Principale", serveur);
    LectBadgeBat lecteurBatimentB = LectBadgeBat("Batiment B - Porte Principale", serveur);
    LectBadgeBat lecteurBatimentC = LectBadgeBat ("Batiment C - Porte Principale", serveur);

    //Salle
    LectBadgeClasse lecteurSalle1 = LectBadgeClasse("Batiment A - Salle1", serveur);
    LectBadgeClasse lecteurSalle2 = LectBadgeClasse("Batiment A - Salle2", serveur);
    LectBadgeClasse lecteurSalle10 = LectBadgeClasse("Batiment A - Salle10", serveur);
    LectBadgeClasse lecteurSalle23 = LectBadgeClasse("Batiment B - Salle33", serveur);
    LectBadgeClasse lecteurSalle36 = LectBadgeClasse("Batiment B - Salle36", serveur);
    LectBadgeClasse lecteurSalle41 = LectBadgeClasse("Batiment C - Salle41", serveur);
    LectBadgeClasse lecteurSalle58 = LectBadgeClasse("Batiment C - Salle58", serveur);

    //Laboratoire
    LectBadgeLab lecteurLabo = LectBadgeLab("Batiment B - Laboratoire", serveur);

    //Bibliotheque
    LectBadgeBibli lecteurBibli = LectBadgeBibli("Batiment A - Bibliotheque", serveur);

    //Zone Securisee
    LectBadgeZoneSecu lecteurSecu = LectBadgeZoneSecu("Batiment B - Zone Securisee", serveur);

    //Cafeteria
    LectBadgeCafet lecteurCafet = LectBadgeCafet("Batiment C - Cafeteria", serveur);

    //Zone Administrative
    LectBadgeZoneAdmin lecteurAdmin = LectBadgeZoneAdmin("Batiment A - Zone Administrative", serveur);

    //Salle des Professeurs
    LectBadgeProf lecteurSalleProf = LectBadgeProf("Batiment A - Salle des Professeurs", serveur);

    cout << "10 lecteurs installes" << endl;

    //5. Ajout des badges et des lecteurs au scheduler
    cout << "\nCONNEXION DES COMPOSANTS..." << endl;

    //Ajout des badges
    ajouterBadge(&lilaBadge);
    ajouterBadge(&pierreBadge);
    ajouterBadge(&hugoBadge);
    ajouterBadge(&martinBadge);
    ajouterBadge(&marieBadge);
    ajouterBadge(&valerieBadge);
    ajouterBadge(&marcBadge);

    //Ajout des lecteurs
    ajouterLecteurBadge(&lecteurBatimentA);
    ajouterLecteurBadge(&lecteurSalle1);
    ajouterLecteurBadge(&lecteurBatimentB);
    ajouterLecteurBadge(&lecteurLabo);
    ajouterLecteurBadge(&lecteurBibli);
    ajouterLecteurBadge(&lecteurSecu);
    ajouterLecteurBadge(&lecteurBatimentC);
    ajouterLecteurBadge(&lecteurCafet);
    ajouterLecteurBadge(&lecteurAdmin);
    ajouterLecteurBadge(&lecteurSalleProf);

    cout <<"Tous les composants connectes" << endl;

    //6. Affichage de la configuration
    cout << "\nCONFIGURATION DU SYSTEME :" << endl;
    cout << "============================" << endl;
    cout << "- Periode de simulation: 7h30 - 19h00" << endl;
    cout << "- Intervalle reel: 1 seconde = 15 minutes simulees" << endl;
    cout << "- Duree reelle: ~46 secondes" << endl;

    //7. Lancement de la simulation complete
    cout << "\nLANCEMENT DE LA SIMULATION COMPLETE" << endl;
    cout << "====================================" << endl;

    cout << "Appuyez sur Entree pour commencer...\n";
    cin.get(); // Pause avant de commencer

    simulation();

    //8. Conclusion
    cout << "\nSIMULATION TERMINEE" << endl;
    cout << "====================" << endl;
    cout << "Resume de la journee dans les logs" << endl;
    cout << "Analysez les motifs de refus d'acces" << endl;
}

void Scheduler::simulation() {
    simulationEnCours = true;
    int cycle = 0;

    cout << "DEBUT DE LA SIMULATION DE LA JOURNEE" << endl;
    ecrireLog("Debut de la simulation", true);
    cout << "Periode: " << getHeureSimulation() << " a " << heureFin << "h" << endl;

    //Tant que l'heure affichee ne correspond pas a la fin de la journee de la simulation, on genere un evenement
    while (simulationEnCours && heureSimulation <= heureFin) {
        cycle++;

        //Affiche dans la console le cycle et l'heure equivalente.
        cout << "\n=== CYCLE " << cycle << " - " << getHeureSimulation() << " ===" << endl;

        //Verifie si c'est l'heure d'ouverture/fermeture
        if (abs(heureSimulation - heureDebut) < 0.01) { //Environ 7h30
            cout << "OUVERTURE DU CAMPUS" << endl;
        }
        else if (abs(heureSimulation - heureFin) < 0.01) { //Environ 19h00
            cout << "FERMETURE DU CAMPUS" << endl;
        }

        //Genere des evenements seulement pendant les heures d'ouverture
        if (estHeureOuverture()) {
            genererEvenementAleatoire();
        } else {
            cout << "Campus ferme - Aucun evenement" << endl;
        }

        //Attend avant le prochain cycle
        this_thread::sleep_for(chrono::milliseconds(intervalleSimulation));

        //Avance le temps de simulation (15 min par cycle)
        incrementerHeure();
    }

    //Annonce la fin de la journee de simulation si tout s'est bien passe
    if (simulationEnCours) {
        cout << "\nSIMULATION TERMINEE - Fin de la journee a " << getHeureSimulation() << endl;
    }
}

bool Scheduler::estHeureOuverture() const {
    return (heureSimulation >= heureDebut && heureSimulation < heureFin);
}

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
    }
    else if ((heureSimulation >= 12.0 && heureSimulation <= 13.0) || //Midi entre 12h / 13h : heure de pointe moderee
        (heureSimulation >= 17.0 && heureSimulation <= 18.0)) { //Soir entre 17h / 18h : heure de pointe moderee
        probabilite = 0.8; //80% : activite elevee
        cout << "HEURE DE POINTE - Activite elevee" << endl;
        }
    else if (heureSimulation > 18.0 && heureSimulation <= 19.0) {
        probabilite = 0.3; //30%, tres faible entree
        cout << "ACTIVITE REDUITE" << endl;
    }
    else { //Activite normale (7h30-8h / 9h-12h / 13h-17h), probabilite deja a 70%
        cout << "ACTIVITE NORMALE" << endl;
    }

    //Permet de generer un nombre aleatoire
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disChance(0, 1); //Genere un nombre decimal entre 0 et 1

    if (disChance(gen) > probabilite) { //Si le chiffre genere est superieur a la probabilite d'evenement, rien ne se passe.
        cout << "Aucun evenement ce cycle" << endl;
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

void Scheduler::incrementerHeure() {
    heureSimulation += 0.25; //15 minutes par cycle

    //Verifie si on a depasse l'heure de fin
    if (heureSimulation > heureFin) {
        simulationEnCours = false;
    }
}

string Scheduler::getHeureSimulation() const {
    int heures = static_cast<int>(heureSimulation); //Enleve la partie decimale de l'heure de la simulation
    int minutes = static_cast<int>((heureSimulation - heures) * 60); //Recupere la partie decimale de l'heure de la simulation

    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", heures, minutes); //Ecrit l'heure dans la forme HH:MM
    return string(buffer);
}

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

void Scheduler::arreterSimulation() {
    simulationEnCours = false;
}