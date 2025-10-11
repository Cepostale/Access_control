#include <iostream>
#include "include/Personne.h"
#include "include/Badge.h"
#include "include/Scheduler.h"
#include "include/Serveur.h"

#include <fstream>


int main() {

    auto jean = Personne("Martin", "Jean", "Enseignant");
    string nom = jean.getNomComplet();
    string statut = jean.getStatut();
    cout << nom << " " << statut << endl;

    auto serveurUnique = Serveur("../DescriptionFile.csv", "LogFile.csv" );
    bool reponse = serveurUnique.loadConfiguration();

    return 0;
}