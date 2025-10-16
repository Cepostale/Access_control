#ifndef LECTEURBADGE_H
#define LECTEURBADGE_H

#include <iostream>
#include "Badge.h"
using namespace std;

class Serveur;

//Classe LecteurBadge est une classe mere pour des portes de batiments ou portes de salles de travail.
class LecteurBadge {
private:
  static int compteurId;
  int idLecteur;
  string localisation; //Descrption du lieu "Batiment - salle/lieu"
  string typePorte; //Batiment,Classe,Laboratoire,ZoneSecurisee,ZoneAdministrative,Bibliothèque,Cafeteria
  Serveur& serv;
public:
  //Constructeur par defaut
  LecteurBadge() = delete;//Si un lecteur est initialise vide, il est supprime car impossible
  //Constructeur par recopie
  LecteurBadge(const LecteurBadge& l): idLecteur(compteurId++), localisation(l.localisation), typePorte(l.typePorte), serv(l.serv) {};
  //Operateur affectation
  LecteurBadge& operator=(const LecteurBadge &l);
  //Destructeur
  virtual ~LecteurBadge(){};


  //Constructeur le plus utilise, tout est renseigne
  LecteurBadge(const string& loc, const string& typeP,Serveur& serveur): idLecteur(compteurId++), serv(serveur), typePorte(typeP), localisation(loc){};

  //Permet de savoir le type de porte pour le mettre dans le fichier log
  virtual string getTypePorte()const = 0;

  //Affiche une ouverture de porte
  void openPorte();

  //Demande l'autorisation d'ouvrir la porte au serveur
  bool askAutorisation( Badge& b, const string& heureSimulation);

  //Permet de savoir la localisation du LecteurBadge
  string getLocalisation()const{return localisation;};
};

#endif //LECTEURBADGE_H
