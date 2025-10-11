#include <iostream>
#include "include/Personne.h"
#include "include/Badge.h"
#include "include/Scheduler.h"
#include "include/Serveur.h"

#include <fstream>


int main() {

    //Creation du serveur
    cout << "\nINITIALISATION DU SERVEUR..." << endl;
    Serveur serveurUnique = Serveur("../DescriptionFile.csv", "../LogFile.txt" );
    //Chargement de la configuration
    bool reponse = serveurUnique.loadConfiguration();

    Scheduler sched = Scheduler(serveurUnique);
    sched.initialisation(serveurUnique);


    return 0;
}