#ifndef HERITAGELECTEUR_H
#define HERITAGELECTEUR_H

#include "LecteurBadge.h"

//Classe LectBadgeBat, correspond aux batiments, heritage public de LecteurBadge
class LectBadgeBat : public LecteurBadge {
public:

    //Constructeur, assigne automatiquement le type de porte = "Batiment"
    LectBadgeBat(const string& loc,Serveur& serveur): LecteurBadge(loc, "Batiment", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "Batiment"; };
};

//Classe LectBadgeClasse, correspond aux classes, heritage public de LecteurBadge
class LectBadgeClasse : public LecteurBadge {
public:
    //Constructeur, assigne automatiquement le type de porte = "Classe"
    LectBadgeClasse(const string& loc,Serveur& serveur): LecteurBadge(loc, "Classe", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "Classe"; };
};

//Classe LectBadgeLab, correspond aux laboratoires, heritage public de LecteurBadge
class LectBadgeLab : public LecteurBadge {
public:
    //Constructeur, assigne automatiquement le type de porte = "Laboratoire"
    LectBadgeLab(const string& loc,Serveur& serveur): LecteurBadge(loc, "Laboratoire", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "Laboratoire"; };
};

//Classe LectBadgeZoneSecu, correspond aux zones securisees, heritage public de LecteurBadge
class LectBadgeZoneSecu : public LecteurBadge {
public:

    //Constructeur, assigne automatiquement le type de porte = "ZoneSecurisee"
    LectBadgeZoneSecu(const string& loc,Serveur& serveur): LecteurBadge(loc, "ZoneSecurisee", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "ZoneSecurisee"; };
};

//Classe LectBadgeZoneAdmin, correspond aux zones administratives, heritage public de LecteurBadge
class LectBadgeZoneAdmin : public LecteurBadge {
public:

    //Constructeur, assigne automatiquement le type de porte = "ZoneAdministrative"
    LectBadgeZoneAdmin(const string& loc,Serveur& serveur): LecteurBadge(loc, "ZoneAdministrative", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "ZoneAdministrative"; };
};

//Classe LectBadgeBibli, correspond à la bibliotheque, heritage public de LecteurBadge
class LectBadgeBibli : public LecteurBadge {
public:

    //Constructeur, assigne automatiquement le type de porte = "Bibliotheque"
    LectBadgeBibli(const string& loc,Serveur& serveur): LecteurBadge(loc, "Bibliotheque", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "Bibliotheque"; };
};

//Classe LectBadgeCafet, correspond à la cafeteria, heritage public de LecteurBadge
class LectBadgeCafet : public LecteurBadge {
public:

    //Constructeur, assigne automatiquement le type de porte = "Cafeteria"
    LectBadgeCafet(const string& loc,Serveur& serveur): LecteurBadge(loc, "Cafeteria", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "Cafeteria"; };
};

//Classe LectBadgeProf, correspond à la salle des professeurs, heritage public de LecteurBadge
class LectBadgeProf : public LecteurBadge {
public:

    //Constructeur, assigne automatiquement le type de porte = "SalleProfesseur"
    LectBadgeProf(const string& loc,Serveur& serveur): LecteurBadge(loc, "SalleProfesseur", serveur){};

    //Renvoie le type de porte
    string getTypePorte() const override { return "SalleProfesseur"; };
};

#endif //HERITAGELECTEUR_H
