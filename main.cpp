#include <iostream>
#include "include/Personne.h"
#include "include/Badge.h"
#include "include/Scheduler.h"
#include "include/Serveur.h"

#include <fstream>


int main() {

    //Creation du scheduler
    Scheduler sched = Scheduler();

    //Lancement de l'initialisation
    sched.initialisation();

    return 0;
}