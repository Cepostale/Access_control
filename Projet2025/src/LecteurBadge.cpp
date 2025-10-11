#include "../include/LecteurBadge.h"
#include "../include/Serveur.h"

LecteurBadge& LecteurBadge::operator=(const LecteurBadge &l) {
  this->idLecteur = l.idLecteur;
  this->localisation = l.localisation;
  this->typePorte = l.typePorte;
  this->serv = l.serv;
  return *this;
}

bool LecteurBadge :: askAutorisation( Badge& b, const string& heureSimulation){
  cout << "Verification d'acces en cours..." << endl;
  cout << "Localisation: " << localisation << endl;
  cout << "Type de porte: " << typePorte;

  return serv.askAcces(b, *this, heureSimulation);
}

string LecteurBadge::getLocalisation() const{
  return localisation;
}

void LecteurBadge::openPorte() {
  cout << "PORTE OUVERTE - Acces autorise" << endl;
  cout << "Localisation: " << localisation << endl;
}
