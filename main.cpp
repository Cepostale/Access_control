#include <iostream>
#include "include/Personne.h"
#include "include/Badge.h"
#include "include/Scheduler.h"
#include "include/Serveur.h"

#include <fstream>


int main() {
    //Creation du serveur
    Serveur serveurUnique = Serveur("../DescriptionFile.csv", "../LogFile.txt" );

    //Creation du scheduler
    Scheduler sched = Scheduler(serveurUnique);
    //Lancement de l'initialisation
    sched.initialisation(serveurUnique);

    return 0;
}