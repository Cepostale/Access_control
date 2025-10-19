#include "../include/LecteurBadge.h"
#include "../include/Serveur.h"

int LecteurBadge::compteurId = 1;

LecteurBadge& LecteurBadge::operator=(const LecteurBadge &l) {
  //Si l'objet appelant est different que celui copie on modifie la localisation et le type de porte, sinon renvoie l'objet appelant
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
  //Retourne la valeur de la demande d'acces du serveur
  return serv.askAcces(b, *this, heureSimulation);
}

void LecteurBadge::openPorte() {
  cout << "PORTE OUVERTE - Acces autorise" << endl;
  cout << "Localisation: " << localisation << endl;
}
