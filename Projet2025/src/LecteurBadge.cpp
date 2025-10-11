#include "../include/LecteurBadge.h"
#include "../include/Serveur.h"

//Initialisation du compteur de lecteur à 1 pour le premier
int LecteurBadge::compteurId = 1;

LecteurBadge& LecteurBadge::operator=(const LecteurBadge &l) {
  if (this != &l) {
    this->localisation = l.localisation;
    this->typePorte = l.typePorte;
    //Pas d'affection de l'id
  }
  return *this;
}

bool LecteurBadge :: askAutorisation( Badge& b, const string& heureSimulation){
  cout << "Verification d'acces en cours..." << endl;
  cout << "Localisation: " << localisation << endl;
  cout << "Type de porte: " << typePorte;

  return serv.askAcces(b, *this, heureSimulation);
}

void LecteurBadge::openPorte() {
  cout << "PORTE OUVERTE - Acces autorise" << endl;
  cout << "Localisation: " << localisation << endl;
}
